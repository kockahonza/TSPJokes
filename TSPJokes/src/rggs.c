#include <stdlib.h>

#include "graph.h"

// Each edge will be a random integer from 0 to 10.
SGraph rgg_simple(int n) {
    int** D = malloc(n*sizeof(int*));
    for (int i = 0; i < n; ++i) {
        D[i] = malloc(n*sizeof(int));
        for (int o = 0; o < i; ++o) {
            D[i][o] = D[o][i];
        }
        D[i][i] = 0;
        for (int o = i+1; o < n; ++o) {
            D[i][o] = rand() % 10;
        }
    }
    return make_sgraph(n, D);
}
