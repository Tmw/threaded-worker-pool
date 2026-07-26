#ifndef WORKER_T_H
#define WORKER_T_H

#include <stdint.h>
#include <pthread.h>

typedef struct worker_t {
    // track own internal ID
    uint32_t idx;

    // track thread id
    pthread_t t;

    // hold reference to jobqueue
    struct jobqueue_t *queue;
} worker_t;

void worker_init(worker_t *w, struct jobqueue_t *q, uint32_t idx);
void worker_run(worker_t *w);

#endif
