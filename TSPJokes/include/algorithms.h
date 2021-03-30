#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

void two_opt_inplace(SGraph g, Perm p, int k);

Perm two_opt_from_random(SGraph g, int k);

Perm greedy(SGraph g);

#endif
