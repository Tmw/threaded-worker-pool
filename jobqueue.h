#ifndef JOBQUEUE_T_H
#define JOBQUEUE_T_H

#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

#include "worker.h"
#include "config.h"
#include "job.h"
#include "dequeue.h"

typedef struct jobqueue_t {
    // contains the list of worker nodes
    worker_t pool[POOL_SIZE];

    // track state of the jobqueue
    pthread_mutex_t state_mutex;
    bool should_exit;

    // track jobs themselves
    pthread_mutex_t jobs_mutex;
    dequeue_t jobs;
} jobqueue_t;

void jobqueue_init(jobqueue_t *q);
void jobqueue_start(jobqueue_t *q);
void jobqueue_wait(jobqueue_t *q);
bool jobqueue_should_exit(jobqueue_t *q);
void jobqueue_request_exit(jobqueue_t *q);
void jobqueue_destroy(jobqueue_t *q);
void jobqueue_push(jobqueue_t *q, job_t *j);
job_t* jobqueue_pop(jobqueue_t *q);

#endif // !JOBQUEUE_T_H
