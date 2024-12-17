#include "e125v1.h"

int main(void) {
    e125_pc m;
    e125_init(&m);

    e125_loadMem(&m, 15, 4); // a
    e125_loadMem(&m, 3, 5); // b
    // 6 - c
    // start - 7
    // move val 6 to adr 8
    e125_loadMem(&m, 10, 7);
    e125_loadMem(&m, 6, 8);
    e125_loadMem(&m, 16, 9);
    // a + b = d (25)
    e125_loadMem(&m, 30, 10);
    e125_loadMem(&m, 25, 11);
    e125_loadMem(&m, 4, 12);
    e125_loadMem(&m, 5, 13);
    // d - c = e (26)
    e125_loadMem(&m, 40, 14);
    e125_loadMem(&m, 26, 15);
    e125_loadMem(&m, 25, 16);
    e125_loadMem(&m, 6, 17);
    // the end
    e125_loadMem(&m, 1, 18);

    e125_run(&m, 7);

    byte val = e125_getMem(&m, 26);
    
    printf("Result is %s: %d\n", val == 2 ? "true" : "wrong", val);
    
    return 0;
}
