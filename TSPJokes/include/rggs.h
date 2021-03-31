#ifndef RGGS_H
#define RGGS_H

#include "graph.h"

// Plain RGGs
//
SGraph rgg_simple(int n, int R);
SGraph rgg_simple10(int n);

// Rigged RGGs - returns a SolvedSGraph which includes a known optimal solution

typedef struct {
    SGraph g;
    Perm p;
} SolvedSGraph;


// A few versions of the Arthur-Frenley algorithm from the paper, quite a bit of repetition
// between the non-metric and metric versions, could be improved probably.
SolvedSGraph rrgg_artfren(int n, int R);
SolvedSGraph rrgg_artfren10(int n);

SolvedSGraph rrgg_artfren_metric(int n, int R);
SolvedSGraph rrgg_artfren_metric10(int n);

#endif
