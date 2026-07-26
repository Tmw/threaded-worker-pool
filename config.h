#ifndef CONFIG_H
#define CONFIG_H

// Pool size: How many workers do we span
// this is a static limit as workers will be stored on the stack.
// will make this dynamic later
#define POOL_SIZE 10

// max queue depth: How many items may be on the pool.
// Hard-coded for now, will switch to a dynamic dequeue / linked list soon
#define MAX_QUEUE_DEPTH 10

#endif
