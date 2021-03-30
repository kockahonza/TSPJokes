#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"
#include "graph.h"
#include "rggs.h"
#include "algorithms.h"

int N = 5;

int xx[4][4] = {
    {0, 1, 2, 3},
    {1, 0, 4, 5},
    {2, 4, 0, 6},
    {3, 5, 6, 0},
};

int main(int argc, char *argv[])
{
    greetings();

    srand(time(NULL));

    int** yy = malloc(4*sizeof(int*));
    for (int i = 0; i < 4; ++i) {
        yy[i] = xx[i];
    }

    SGraph g;

    g = rgg_simple(N);
    Perm p = random_perm(N);

    print_perm(p);
    two_opt_inplace(g, p, -1);
    printf("--------------------\n");
    print_sgraph(g);
    printf("--------------------\n");
    print_perm(p);

}
