#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int n;
    int** D;
} SGraph;

typedef struct {
    int n;
    int* P;
} Perm;

SGraph make_sgraph(int n, int** D);
SGraph make_sgraph_copyD(int n, int** D);


int get_dist(SGraph g, int i, int j);

void print_sgraph_D(SGraph g);

int is_metric(SGraph g);


Perm make_perm(int n, int* P);
Perm make_perm_copyP(int n, int* P);


void print_perm(Perm p);

Perm random_perm(int n);

#endif
