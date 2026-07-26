#include <stdio.h>
#include <unistd.h>

#include "job.h"
#include "worker.h"
#include "jobqueue.h"

void* _worker_run(void *arg);

void worker_init(worker_t *w, jobqueue_t *q, uint32_t idx) {
    w->idx = idx;
    w->queue = q;
}

void worker_run(worker_t *w) {
    pthread_create(&w->t, NULL, &_worker_run, (void*) w);
}

void* _worker_run(void *arg) {
    worker_t *w = (worker_t*) arg;
    jobqueue_t *q = w->queue;

    printf("[INFO] worker_id=%d, state=started\n", w->idx);

    while(!jobqueue_should_exit(q)) {
        job_t *j = jobqueue_pop(q);
        if (j == NULL) {
            printf("[INFO] worker_id=%d, state=no_job\n", w->idx);
            sleep(1);
            continue;
        }

        printf("[INFO] worker_id=%d\n", w->idx);
        j->run(j->args);

        job_destroy(j);

        sleep(1);
    }

    printf("[INFO] worker_id=%d, state=closing\n", w->idx);

    return NULL;
}
