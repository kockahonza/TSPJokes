#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "graph.h"

void two_opt_inplace(SGraph g, Perm p, int k) {
    int better = 1;
    int count = 0;
    while (better && ((k == -1) || (count < k))) {
        better = 0;
        count += 1;
        for (int j = 0; j < g.n-1; ++j) {
            for (int i = 0; i < j; ++i) {
                int pi = (i+g.n-1)%g.n;
                int pj = (j+1)%g.n;
                if ((get_dist(g, p.P[pi], p.P[j]) + get_dist(g, p.P[i], p.P[pj])) <
                    (get_dist(g, p.P[pi], p.P[i]) + get_dist(g, p.P[j], p.P[pj]))) {

                    int n = i;
                    int m = j;
                    int temp;
                    while (n < m) {
                        temp = p.P[n];
                        p.P[n] = p.P[m];
                        p.P[m] = temp;
                        n += 1;
                        m -= 1;
                    }

                    better = 1;
                }
            }
        }
    }
    return p;
}

Perm two_opt_from_random(SGraph g, int k) {
    Perm p = random_perm(g.n);
    two_opt_inplace(g, p, k);
    return p;
}

Perm greedy(SGraph g) {
    Perm p;
    p.n = g.n;
    p.P = malloc(p.n*sizeof(int));
    p.P[0] = 0;
}
