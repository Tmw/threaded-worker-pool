#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "jobqueue.h"
#include "dequeue.h"
#include "job.h"

void jobqueue_init(jobqueue_t *q) {
  q->should_exit = false;

  assert(pthread_mutex_init(&q->state_mutex, NULL) == 0 &&
         "error creating state mutex");

  assert(pthread_mutex_init(&q->jobs_mutex, NULL) == 0 &&
         "error creating jobs mutex");

  // initialize workers
  for (uint32_t i = 0; i < POOL_SIZE; i++) {
    worker_init(&q->pool[i], q, i);
  }
}

void jobqueue_start(jobqueue_t *q) {
  for (uint32_t i = 0; i < POOL_SIZE; i++) {
    worker_run(&q->pool[i]);
  }
}

void jobqueue_wait(jobqueue_t *q) {
  for (uint32_t i = 0; i < POOL_SIZE; i++) {
    pthread_join(q->pool[i].t, NULL);
  }
}

bool jobqueue_should_exit(jobqueue_t *q) {
  int res = pthread_mutex_lock(&q->state_mutex);
  if (res != 0) {
    printf("error obtaining lock for should_exit: %d\n", res);
    assert(false);
  }

  bool should_exit = q->should_exit;

  res = pthread_mutex_unlock(&q->state_mutex);
  if (res != 0) {
    printf("error releasing lock for should_exit: %d\n", res);
    assert(false);
  }

  return should_exit;
}

void jobqueue_request_exit(jobqueue_t *q) {
  int res = pthread_mutex_lock(&q->state_mutex);
  if (res != 0) {
    printf("error obtaining lock for should_exit: %d\n", res);
    assert(false);
  }

  q->should_exit = true;

  res = pthread_mutex_unlock(&q->state_mutex);
  if (res != 0) {
    printf("error releasing lock for should_exit: %d\n", res);
    assert(false);
  }
}

void jobqueue_destroy(jobqueue_t *q) {
  // TODO: rewrite to the new assert style i came up with
  //
  int res = pthread_mutex_destroy(&q->jobs_mutex);
  assert(res == 0 && "pthread_mutex_destroy returned error");
}

void jobqueue_push(jobqueue_t *q, job_t *j) {
  assert(pthread_mutex_lock(&q->jobs_mutex) == 0 &&
         "error obtaining lock for jobqueue_push");

  dequeue_push_back(&q->jobs, j);

  assert(pthread_mutex_unlock(&q->jobs_mutex) == 0 &&
         "error releasing lock for jobqueue_push");
}

job_t *jobqueue_pop(jobqueue_t *q) {
  assert(pthread_mutex_lock(&q->jobs_mutex) == 0 &&
         "error obtaining lock for jobqueue_pop");

  job_t *job = (job_t *) dequeue_pop_front(&q->jobs);

  assert(pthread_mutex_unlock(&q->jobs_mutex) == 0 &&
         "error releasing lock for jobqueue_pop");

  return job;
}
