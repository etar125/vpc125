#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#include "tinyss.h"

void help() {
    printf("lite125 v0.1.3\n\
lite125 [options] binary_file\n\
\n\
    -s --save <file>        Save memory on exit\n\
    -l --load <file>        Load memory from file\n\
    -e --extension <file>   Load extension\n\
\n\
    -v --version            Version\n\
    -h --help               Help\n\
");
}

unsigned char memory[256];

void _reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while(start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
} char* _itoa(int num, char* str, int base) {
    int i = 0;
    bool m = false;
    if(num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if(num < 0 && base == 10) {
        m = true;
        num = -num;
    }
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
    if(m) { str[i++] = '-'; }
    str[i] = '\0';
    _reverse(str, i);
    return str;
}

int main(int argc, char **argv) {
    if(argc == 1) { help(); return 0; }
    char *sf = NULL, *lf = NULL, *ext = "lite8.tss";
    unsigned char file[256];
    char *ecode;
    FILE *f, *ef; size_t fsz, esz;
    tss_varlist list;
    tss_vlinit(&list);

    ef = fopen(ext, "rb");
    if(ef) {
        fseek(ef, 0, SEEK_END);
        esz = ftell(ef);
        rewind(ef);
        ecode = malloc(esz);
        fread(ecode, 1, esz, ef);
    }
    
    short fp;
    for(short a = 0; a < 256; a++) { memory[a] = 0; }
    
    for(int i = 1; i < argc; i++) {
        if(!strcmp(argv[i], "-s") || !strcmp(argv[i], "--save")) {
            if(i + 1 == argc) {
                printf("save: excepted file name\n");
                return 1;
            } i++;
            sf = argv[i];
        } else if(!strcmp(argv[i], "-l") || !strcmp(argv[i], "--load")) {
            if(i + 1 == argc) {
                printf("load: excepted file name\n");
                return 1;
            } i++;
            lf = argv[i];
        } else if(!strcmp(argv[i], "-e") || !strcmp(argv[i], "--extension")) {
            if(i + 1 == argc) {
                printf("extension: excepted file name\n");
                return 1;
            } i++;
            ext = argv[i];
            if(ef) {
                fclose(ef);
                free(ecode);
            }
            ef = fopen(ext, "rb");
            if(ef) {
                fseek(ef, 0, SEEK_END);
                esz = ftell(ef);
                rewind(ef);
                ecode = malloc(esz);
                fread(ecode, 1, esz, ef);
            }
        } else if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) { help(); }
        else if(!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")) { printf("lite125 v0.1.0\n"); }
        else {
            if(!ef) {
                printf("no extension\n");
                return 1;
            } f = fopen(argv[i], "r");
            if(!f) {
                printf("file error\n");
                return 1;
            }
            fseek(f, 0L, SEEK_END);
            fsz = ftell(f);
            rewind(f);
            if(fsz > 256) {
                printf("file size is bigger than 256 bytes\n");
                return 1;
            } fgets(file, fsz, f);
            fp = 1;
            short i = file[0];
            while(fp < fsz) {
                if(i == 256) {
                    printf("mem error\n");
                    return 1;
                }
                memory[i] = file[fp];
                i++, fp++;
            }

            tss_printerrv(tss_docode(&list, ecode, esz), ecode, esz);
            
            fclose(f);
        }
    } if(ef) { fclose(ef); }
    free(ecode);
}

void tss_gfunc(tss_varlist *list, tss_stack *stack, char *name) {
    if(strcmp(name, "get") == 0) {
        char *var = tss_pop(stack), *pos = tss_pop(stack), *b = malloc(13);
        short i = atoi(pos);
        if(i < 256) {
          tss_setvar(list, var, _itoa(memory[i], b, 10)); 
        } free(pos); free(var); free(b);
        
    } else if(strcmp(name, "set") == 0) {
        char *val = tss_pop(stack), *pos = tss_pop(stack);
        short i = atoi(pos);
        if(i < 256) {
            memory[i] = atoi(val);
        } free(pos); free(val);
    } else if(strcmp(name, "print") == 0) {
        char *m = tss_pop(stack);
        printf("%s", m);
        free(m);
    }
}
