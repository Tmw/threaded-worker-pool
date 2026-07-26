#ifndef JOB_T_H
#define JOB_T_H

typedef struct job_t {
    void (*run)(void *args);
    unsigned char args[];
} job_t;

job_t *job_create(void (*run_func)(void*), void* args, size_t arg_size);
void job_destroy(job_t *job);
#endif // !JOB_T_H
