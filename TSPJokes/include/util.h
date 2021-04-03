#ifndef UTIL_H
#define UTIL_H

// Cell struct for a doubly-linked-list of integers
typedef struct IntDLL {
    struct IntDLL* prev;
    int val;
    struct IntDLL* next;
} IntDLL;

#endif
