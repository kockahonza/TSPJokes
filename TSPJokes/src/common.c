#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void greetings() {
    printf("--------------------\n");
#if DEBUG
    printf("Debug mode is %d\n", DEBUG);
#endif
#if SAFE
    printf("Safe mode is %d\n", SAFE);
#endif
    printf("--------------------\n");
}

void error(int ercode, char* msg) {
    printf(msg);
    exit(ercode);
}

void error42(char* msg) {
    error(42, msg);
}

