#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "rggs.h"

// Each edge will be a random integer from 0 to R.
SGraph rgg_simple(int n, int R) {
    int** D = malloc(n*sizeof(int*));
    for (int i = 0; i < n; ++i) {
        D[i] = malloc(n*sizeof(int));
        for (int o = 0; o < i; ++o) {
            D[i][o] = D[o][i];
        }
        D[i][i] = 0;
        for (int o = i+1; o < n; ++o) {
            D[i][o] = rand() % R;
        }
    }
    return make_sgraph(n, D);
}

SGraph rgg_simple10(int n) {
    return rgg_simple(n, 10);
}

SolvedSGraph rrgg_artfren(int n, int R) {
    if (R < 1) {
        R = 10;
    }
    // Initialize the graph and get a random permutation
    SolvedSGraph sg;
    sg.p = random_perm(n);

    // Initialize the dist matrix with 0s on the diagonal and -1s everywhere else
    int** D = malloc(n*sizeof(int*));
    for (int i = 0; i < n; ++i) {
        D[i] = malloc(n*sizeof(int));
        for (int o = 0; o < n; ++o) {
            D[i][o] = -1;
        }
        D[i][i] = 0;
    }

    // Setup the A matrix with random values in [1, floor(R/2)]
    int Abound = R/2;
    int* A = malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        A[i] = 1 + (rand() % Abound);
    }

    // Set the dists along the random permutation
    int k = sg.p.P[n-1];
    int l = sg.p.P[0];
    D[k][l] = D[l][k] = A[k] + A[l];
    for (int i = 0; i < n-1; ++i) {
        k = sg.p.P[i];
        l = sg.p.P[i+1];
        D[k][l] = D[l][k] = A[k] + A[l];
    }

    // Set all the other dists
    int temp;
    for (int i = 0; i < n; ++i) {
        for (int o = i+1; o < n; ++o) {
            if (D[i][o] == -1) {
                temp = A[i] + A[o];
                if (temp == R) {
                    D[i][o] = D[o][i] = temp;
                } else {
                    D[i][o] = D[o][i] = temp + (rand() % (R - temp));
                }
            }
        }
    }

    free(A);

    sg.g = make_sgraph(n, D);

    return sg;
}

SolvedSGraph rrgg_artfren10(int n) {
    return rrgg_artfren(n, 10);
}

SolvedSGraph rrgg_artfren_metric(int n, int R) {
    if (R < 1) {
        R = 10;
    }
    // Initialize the graph and get a random permutation
    SolvedSGraph sg;
    sg.p = random_perm(n);

    // Initialize the dist matrix with 0s on the diagonal and -1s everywhere else
    int** D = malloc(n*sizeof(int*));
    for (int i = 0; i < n; ++i) {
        D[i] = malloc(n*sizeof(int));
        for (int o = 0; o < n; ++o) {
            D[i][o] = -1;
        }
        D[i][i] = 0;
    }

    // Setup the A matrix with random values in [1, floor(R/2)] and let gamma = min(2A[i]) for any i
    int Abound = R/2;
    int* A = malloc(n*sizeof(int));
    int gamma = Abound;
    for (int i = 0; i < n; ++i) {
        A[i] = 1 + (rand() % Abound);
        if (A[i] < gamma) {
            gamma = A[i];
        }
    }
    gamma = gamma + gamma;

    // Set the dists along the random permutation
    int k = sg.p.P[n-1];
    int l = sg.p.P[0];
    D[k][l] = D[l][k] = A[k] + A[l];
    for (int i = 0; i < n-1; ++i) {
        k = sg.p.P[i];
        l = sg.p.P[i+1];
        D[k][l] = D[l][k] = A[k] + A[l];
    }

    // Set all the other dists
    int temp1;
    int temp2;
    for (int i = 0; i < n; ++i) {
        for (int o = i+1; o < n; ++o) {
            if (D[i][o] == -1) {
                temp1 = A[i] + A[o];
                temp2 = R - temp1;
                if (temp2 == 0) {
                    D[i][o] = D[o][i] = temp1;
                } else {
                    D[i][o] = D[o][i] = temp1 + (rand() % ((temp2 < gamma) ? temp2 : gamma));
                }
            }
        }
    }

    free(A);

    sg.g = make_sgraph(n, D);

    return sg;
}

SolvedSGraph rrgg_artfren_metric10(int n) {
    return rrgg_artfren_metric(n, 10);
}

