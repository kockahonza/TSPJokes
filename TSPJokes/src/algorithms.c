#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "graph.h"
#include "util.h"

// Cell struct for a doubly-linked-list of references to pairs of IntDLLs
typedef struct MagickDLL {
    struct MagickDLL* prev;
    int index;
    int len;
    int* options;
    struct MagickDLL* next;
} MagickDLL;

Perm exact_branch_bound(SGraph g) {

    int* min_detour = malloc(g.n*sizeof(int));
    int best_score1, best_score2;
    int score;
    /* printf("min_detour - "); */
    for (int i = 1; i < g.n; ++i) {
        best_score1 = best_score2 = get_dist(g, i, (i+1)%g.n);
        for (int o = 0; o < i; ++o) {
            score = get_dist(g, i, o);
            if (score < best_score1) {
                best_score1 = score;
            } else if (score < best_score2) {
                best_score2 = score;
            }
        }
        for (int o = i+1; o < g.n; ++o) {
            score = get_dist(g, i, o);
            if (score < best_score1) {
                best_score1 = score;
            } else if (score < best_score2) {
                best_score2 = score;
            }
        }
        min_detour[i] = (best_score1 + best_score2) / 2;
        /* printf("%d (%d + %d), ", min_detour[i], best_score1, best_score2); */
    }
        /* printf("\n"); */

    int* bestP = malloc(g.n*sizeof(int));
    for (int i = 0; i < g.n; ++i) {
        bestP[i] = i;
    }
    int best_score = P_score_on_sgraph(g, bestP);

    int* curP = malloc(g.n*sizeof(int));
    curP[0] = 0;
    int curP_len = 1;
    int curP_score = 0;

    MagickDLL* notes = malloc(sizeof(MagickDLL));

    notes->index = 0;
    notes->len = g.n - 1;
    notes->options = malloc(notes->len*sizeof(int));
    for (int i = 0; i < g.n-1; ++i) {
        (notes->options)[i] = i+1;
    }

    MagickDLL* cur_notes = notes;

    int temp;
    /* double stat_one = 0; */
    /* double stat_two = 0; */
    while ((notes->index < notes->len) || (curP_len > 1)) {
        /* printf("\tcc: %d, %d, %d, %d, (", cur_notes->index, cur_notes->len, curP_len, curP_score); */
        /* for (int i = 0; i < cur_notes->len; ++i) { */
        /*     printf("%d, ", cur_notes->options[i]); */
        /* } */
        /* printf(") ["); */
        /* for (int i = 0; i < g.n; ++i) { */
        /*     printf("%d, ", curP[i]); */
        /* } */
        /* printf("]\n"); */
        if (cur_notes->index < cur_notes->len) {
            // set the (possibly) next element of curP and reflect it in the score
            curP[curP_len] = cur_notes->options[cur_notes->index];
            curP_score += get_dist(g, curP[curP_len-1], curP[curP_len]);

            // temp will be used to store the best possible path starting with curP
            temp = curP_score;

            // allocate the next notes
            cur_notes->next = malloc(sizeof(MagickDLL));

            // set the easy next notes fields
            cur_notes->next->prev = cur_notes;
            cur_notes->next->index = 0;
            cur_notes->next->len = cur_notes->len - 1;

            // now copy all the nodes that still need dto be visited by curP and add their minimum detiour value to temp
            cur_notes->next->options = malloc(cur_notes->next->len*sizeof(int));
            for (int i = 0; i < cur_notes->index; ++i) {
                cur_notes->next->options[i] = cur_notes->options[i];
                temp += min_detour[cur_notes->options[i]];
            }
            for (int i = cur_notes->index; i < cur_notes->next->len; ++i) {
                cur_notes->next->options[i] = cur_notes->options[i+1];
                temp += min_detour[cur_notes->options[i+1]];
            }

            // update the relevant indiced based on whether there's a chance of getting a better value
            cur_notes->index += 1;
            /* stat_two += 1; */
            if (temp < best_score) {
                /* printf("Y, %d, %d\n", temp, best_score); */
                /* stat_one += 1; */
                curP_len += 1;
                cur_notes = cur_notes->next;
            } else {
                /* printf("N, %d, %d\n", temp, best_score); */
                curP_score -= get_dist(g, curP[curP_len-1], curP[curP_len]);
                free(cur_notes->next->options);
                free(cur_notes->next);
            }
        } else {
            if (curP_len == g.n) {
                temp = curP_score + get_dist(g, curP[curP_len-1], curP[0]);
                /* printf("Heyo:"); */
                /* for (int i = 0; i < g.n; ++i) { */
                /*     printf("%d, ", curP[i]); */
                /* } */
                /* printf(" - %d, %d\n", curP_score, temp); */
                if (temp < best_score) {
                    for (int i = 0; i < g.n; ++i) {
                        bestP[i] = curP[i];
                        
                    }
                    best_score = temp;
                }
            }
            curP_len -= 1;
            curP_score -= get_dist(g, curP[curP_len], curP[curP_len-1]);

            cur_notes = cur_notes->prev;
            free(cur_notes->next->options);
            free(cur_notes->next);
        }
    }

    free(notes->options);
    free(notes);
    free(curP);
    /* printf("----------- %f, %f, %f -----------\n", stat_one, stat_two, stat_one / stat_two); */
    return make_perm(g.n, bestP);
}

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

    IntDLL* left_mem = malloc((g.n-1)*sizeof(IntDLL));
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

    IntDLL* best_cell;
    int best_score;

    IntDLL* first_checked_cell = left_mem;

    IntDLL* cur_cell;
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
