#include <stdio.h>

#define byte unsigned char

typedef struct {
    byte memory[256];
    byte registers;
    byte other;
    byte position;
} e125_pc;

void e125_init(e125_pc *m) {
    m->position = 0;
    m->registers = 0;
    m->other = 4;
    for(short i = 0; i < 256; i++) {
        m->memory[i] = 0;
    }
}

void e125_loadMem(e125_pc *m, byte val, byte pos) {
    m->memory[pos] = val;
} byte e125_getMem(e125_pc *m, byte pos) {
    return m->memory[pos];
}

typedef enum {
    MoveA = 10, // move ADR value
    MoveB = 11, // move ADR adr
    AddA = 30, // add adr adr1 adr2
    AddB = 31, // add adr adr1 value
    AddC = 32, // add adr value value
    SubstractA = 40, // ^^^
    SubstractB = 41,
    SubstractC = 42, // value adr1
    SubstractD = 43,
    End = 1
} e125_opcodes;

void e125_run(e125_pc *m, byte pos) {
    if(pos >= m->other) {
        m->position = pos;
        while(m->position < 255) {
            e125_opcodes opcode = e125_getMem(m, m->position);

            if(opcode == End) break;

            else if(opcode == MoveA) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val = e125_getMem(m, m->position++);
                e125_loadMem(m, val, adr);
            } else if(opcode == MoveB) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val = e125_getMem(m, e125_getMem(m, m->position++));
                e125_loadMem(m, val, adr);
            }

            else if(opcode == AddA) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val1 = e125_getMem(m, e125_getMem(m, m->position++));
                byte val2 = e125_getMem(m, e125_getMem(m, m->position++));
                e125_loadMem(m, val1 + val2, adr);
            } else if(opcode == AddB) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val1 = e125_getMem(m, e125_getMem(m, m->position++));
                byte val2 = e125_getMem(m, m->position++);
                e125_loadMem(m, val1 + val2, adr);
            } else if(opcode == AddC) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val1 = e125_getMem(m, m->position++);
                byte val2 = e125_getMem(m, m->position++);
                e125_loadMem(m, val1 + val2, adr);
            }

            else if(opcode == SubstractA) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val1 = e125_getMem(m, e125_getMem(m, m->position++));
                byte val2 = e125_getMem(m, e125_getMem(m, m->position++));
                e125_loadMem(m, val1 - val2, adr);
            } else if(opcode == SubstractB) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val1 = e125_getMem(m, e125_getMem(m, m->position++));
                byte val2 = e125_getMem(m, m->position++);
                e125_loadMem(m, val1 - val2, adr);
            } else if(opcode == SubstractB) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val1 = e125_getMem(m, m->position++);
                byte val2 = e125_getMem(m, e125_getMem(m, m->position++));
                e125_loadMem(m, val1 - val2, adr);
            } else if(opcode == SubstractD) {
                m->position++;
                byte adr = e125_getMem(m, m->position++);
                byte val1 = e125_getMem(m, m->position++);
                byte val2 = e125_getMem(m, m->position++);
                e125_loadMem(m, val1 - val2, adr);
            } else m->position++;
        } m->position = 0;
    }
}
