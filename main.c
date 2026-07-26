#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>

#include "jobqueue.h"
#include "job.h"

struct job_args {
    char name[20];
    int age;
};

void example_job(void* args) {
    struct job_args job_args = *(struct job_args*) args;
    printf("Saying hello to %s (aged %d)\n", job_args.name, job_args.age);
}

int main(){
    jobqueue_t q = {0};
    jobqueue_init(&q);
    jobqueue_start(&q);

    for (size_t i = 0; i < 100; i++) {
        struct job_args args = {
            .age = i,
        };
        sprintf(args.name, "dummy job %zu", i);

        job_t *j1 = job_create(&example_job, (void *)&args, sizeof(struct job_args));
        jobqueue_push(&q, j1);
    }

    jobqueue_wait(&q);
    jobqueue_request_exit(&q);

    return 0;
}
