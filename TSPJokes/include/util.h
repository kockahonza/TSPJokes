#ifndef UTIL_H
#define UTIL_H

// Single-linked-list cell
typedef struct SLLCell {
    int val;
    struct SLLCell* next;
} SLLCell;

// Doubly-linked-list cell
typedef struct DLLCell {
    struct DLLCell* prev;
    int val;
    struct DLLCell* next;
} DLLCell;

#endif
