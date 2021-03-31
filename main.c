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
    SolvedSGraph sg;

    /* for (int i = 0; i < 10; ++i) { */
    /*     sg = rrgg_artfren_metric10(N); */
    /*     printf("%d, ", is_metric(sg.g)); */
    /* } */
    /* printf("\n"); */

    sg = rrgg_artfren_metric10(N);
    printf("--------------------\n");
    print_sgraph_D(sg.g);
    printf("--------------------\n");
    print_perm(sg.p);
    printf("--------------------\n");
    printf("%d\n", is_metric(sg.g));

    /* g = rgg_simple10(N); */
    /* printf("--------------------\n"); */
    /* print_sgraph_D(g); */
    /* printf("--------------------\n"); */
    /* printf("%d\n", is_metric(g)); */
}
