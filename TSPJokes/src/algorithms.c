#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "graph.h"
#include "util.h"

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
}

Perm two_opt_from_random(SGraph g, int k) {
    Perm p = random_perm(g.n);
    two_opt_inplace(g, p, k);
    return p;
}

Perm greedy(SGraph g) {
    int* P = malloc(g.n*sizeof(int));
    P[0] = 0;

    DLLCell* left_mem = malloc((g.n-1)*sizeof(DLLCell));
    left_mem[0].prev = left_mem + g.n - 2;
    left_mem[0].val = g.n - 1;
    left_mem[0].next = left_mem + 1;
    for (int i = 1; i < g.n-2; ++i) {
        left_mem[i].prev = left_mem + i - 1;
        left_mem[i].val = i;
        left_mem[i].next = left_mem + i + 1;
    }
    left_mem[g.n-2].prev = left_mem + g.n - 2;
    left_mem[g.n-2].val = g.n - 2;
    left_mem[g.n-2].next = left_mem;

    DLLCell* best_cell;
    int best_score;

    DLLCell* first_checked_cell = left_mem;

    DLLCell* cur_cell;
    int cur_score;
    for (int i = 0; i < g.n - 1; ++i) {
        cur_cell = best_cell = first_checked_cell;
        best_score = get_dist(g, P[i], best_cell->val);
        while (cur_cell != first_checked_cell) {
            cur_score = get_dist(g, P[i], cur_cell->val);
            if (cur_score < best_score) {
                best_cell = cur_cell;
                best_score = cur_score;
            }
            cur_cell = cur_cell->next;
        }
        P[i+1] = best_cell->val;
        best_cell->prev->next = best_cell->next;
        best_cell->next->prev = best_cell->prev;
        first_checked_cell = best_cell->next;
    }

    free(left_mem);

    return make_perm(g.n, P);
}
