#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

Perm exact_branch_bound(SGraph g);

void two_opt_inplace(SGraph g, Perm p, int k);
Perm two_opt_from_random(SGraph g, int k);

Perm greedy(SGraph g);

#endif
