#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "job.h"

job_t *job_create(void (*run_func)(void *), void* args, size_t arg_size) {
    job_t *job = malloc(sizeof(job_t) + arg_size);
    memcpy(job->args, args, arg_size);
    job->run = run_func;
    return job;
}

void job_destroy(job_t *job) {
  free(job);
}
