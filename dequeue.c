#include <stdlib.h>
#include "dequeue.h"

typedef struct dequeue_node_t {
    void *item;
    dequeue_node_t *next;
    dequeue_node_t *prev;
} dequeue_node_t;

void dequeue_push_back(dequeue_t *d, void *n) {
  dequeue_node_t *node = malloc(sizeof(dequeue_node_t));
  node->item = n;

  // set prev item if exists
  if (d->last != NULL) {
    node->prev = d->last;
    d->last->next = node;
  }

  // set as the first item if its the first
  if (d->first == NULL) {
    d->first = node;
  }

  // it always becomes the last item
  d->last = node;
  d->len++;
}

void dequeue_push_front(dequeue_t *d, void *n) {
  dequeue_node_t *node = malloc(sizeof(dequeue_node_t));
  node->item = n;

  // set prev item if exists
  if (d->first != NULL) {
    node->next = d->first;
    d->first->prev = node;
  }

  // set as the last item if its the first
  if (d->last == NULL) {
    d->last = node;
  }

  // it always becomes the first item
  d->first = node;
  d->len++;
}

void* dequeue_pop_front(dequeue_t *d) {
  if (d->first == NULL) {
    return NULL;
  }

  dequeue_node_t *node = d->first;
  d->first = node->next;

  if (node->next != NULL) {
    node->next->prev = NULL;
  }

  void* item = node->item;
  free(node);
  d->len--;
  return item;
}

void* dequeue_pop_back(dequeue_t *d) {
  if (d->last == NULL) {
    return NULL;
  }

  dequeue_node_t *node = d->last;
  d->last = node->prev;

  if (node->prev != NULL) {
    node->prev->next = NULL;
  }

  void* item = node->item;
  free(node);
  d->len--;
  return item;
}

void dequeue_drop_all(dequeue_t *d){
  while(d->len > 0) {
    dequeue_pop_front(d);
  }
}

