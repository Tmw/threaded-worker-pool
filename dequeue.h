#ifndef DEQUEUE_T_H
#define DEQUEUE_T_H

#include <stdint.h>

typedef struct dequeue_node_t dequeue_node_t;

typedef struct dequeue_t {
    dequeue_node_t *first;
    dequeue_node_t *last;
    uint64_t len;
} dequeue_t;

void dequeue_push_front(dequeue_t *d, void *n);
void dequeue_push_back(dequeue_t *d, void *n);
void* dequeue_pop_front(dequeue_t *d);
void* dequeue_pop_back(dequeue_t *d);
void dequeue_drop_all(dequeue_t *d);

#endif // !DEQUEUE_T_H
