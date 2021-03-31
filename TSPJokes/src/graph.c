#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "graph.h"

SGraph make_sgraph(int n, int** D) {
    SGraph g;
    g.n = n;
    g.D = D;
#if SAFE
    if (n <= 0) {
        error42("graph.c:make_perm: n wasn't bigger than 0");
    }
    for (int i = 0; i < n; ++i) {
        if (g.D[i][i] != 0) {
            error42("graph.c:make_sgraph: There is a non-zero element in the diagonal of the dimension matrix.\n");
        }
        for (int o = i+1; o < n; ++o) {
            if (g.D[i][o] != g.D[o][i]) {
                error42("graph.c:make_sgraph: The dimensions matrix isn't symmetric.\n");
            }
        }
    }
#endif
    return g;
}

SGraph make_sgraph_copyD(int n, int** D) {
    int** copiedD = malloc(n*sizeof(int*));
    for (int i = 0; i < n; ++i) {
        copiedD[i] = malloc(n*sizeof(int));
        memcpy(copiedD[i], D[i], n*sizeof(int));
    }
    return make_sgraph(n, copiedD);
}

int get_dist(SGraph g, int i, int j) {
#if SAFE
    if ((i < 0) || (j < 0) || (j >= g.n) || (i >= g.n)) {
        error42("graph.c:get_dist: Either i or j were outside the [0, n) range.");
    }
#endif
    return g.D[i][j];
}

void print_sgraph_D(SGraph g) {
    for (int i = 0; i < g.n; ++i) {
        for (int o = 0; o < g.n; ++o) {
            /* printf("\t"); */
            printf("%d\t", get_dist(g, i, o));
        }
        printf("\n");
    }
}

int is_metric(SGraph g) {
    for (int i = 0; i < g.n; ++i) {
        for (int o = i+1; o < g.n; ++o) {
            for (int p = o+1; p < g.n; ++p) {
                if (((g.D[i][o] + g.D[o][p]) < g.D[i][p]) ||
                    ((g.D[i][p] + g.D[p][o]) < g.D[i][o]) ||
                    ((g.D[o][i] + g.D[i][p]) < g.D[o][p])) {
                    return 0;
                }
            }
        }
    }
    return 1;
}


Perm make_perm(int n, int* P) {
    Perm p;
    p.n = n;
    p.P = P;
#if SAFE
    if (n <= 0) {
        error42("graph.c:make_perm: n wasn't bigger than 0");
    }
    int* check = malloc(n*sizeof(char));
    for (int i = 0; i < n; ++i) {
        check[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        if ((P[i] < 0) || (P[i] >= n) || (check[P[i]])) {
            error42("graph.c:make_perm: The permutation isn't valid, either there is an element outisde the range [0, n) or not all elements are present\n");
        }
    }
    free(check);
#endif
    return p;
}

Perm make_perm_copyP(int n, int* P) {
    int* copiedP = malloc(n*sizeof(int));
    memcpy(copiedP, P, n*sizeof(int));
    return make_perm(n, copiedP);
}

void print_perm(Perm p) {
    for (int i = 0; i < p.n; ++i) {
        printf("%d\t", p.P[i]);
    }
    printf("\n");
}

Perm random_perm(int n) {
    Perm p;
    p.n = n;
    p.P = malloc(n*sizeof(int));

    int j;
    for (int i = 0; i < n; ++i) {
        j = rand() % (i+1);
        if  (j != i) {
            p.P[i] = p.P[j];
        }
        p.P[j] = i;
    }

    return p;
}
