/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
  queue_t *q = malloc(sizeof(queue_t));
  if (q == NULL)
  {
    return NULL;
  }
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  if(q == NULL){
    return;
  }

  if(q->head == NULL && q->tail == NULL){
    free(q);
    return;
  }

  list_ele_t *cur = q->head;
  while (cur != NULL)
  {
    list_ele_t *next = cur->next;
    free(cur);
    cur = next;
  }
  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
  if (q == NULL)
  {
    return 0;
  }

  list_ele_t *newh = malloc(sizeof(list_ele_t));
  if (newh == NULL)
  {
    return 0;
  }

  newh->value = v;
  if (q->head == NULL)
  {
    newh->next = NULL;
    q->tail = newh;
    q->head = newh;
    q->size += 1;
    return 1;
  }

  newh->next = q->head;
  q->head = newh;
  q->size += 1;
  return 1;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
  if (q == NULL)
  {
    return 0;
  }

  list_ele_t *new = malloc(sizeof(list_ele_t));
  if (new == NULL)
  {
    return 0;
  }

  new->value = v;
  new->next = NULL;

  if (q->head==NULL)
  {
    q->head = new;
    q->tail = new;
    q->size +=1;
    return 1;
  }

  q->tail->next = new;
  q->tail = new;
  q->size += 1;
  return 1;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
  if (q == NULL)
  {
    return 0;
  }

  if (q->head == NULL)
  {
    return 0;
  }

  if(q->head == q->tail || q->size == 1){
    if (vp != NULL)
    {
      *vp = q->head->value;
    }

    q->size = 0;
    q->tail = NULL;

    free(q->head);
    q->head = NULL;
    return 1;
  }

  list_ele_t *head = q->head;
  if (vp != NULL)
  {
    *vp = q->head->value;
  }
  q->head = q->head->next;
  free(head);
  q->size -= 1;
  return 1;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  if (q == NULL)
  {
    return 0;
  }
  
  if(q->head == NULL){
    return 0;
  }

  return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
  if (q == NULL || q->size <=1)
  {
    return;
  }

  list_ele_t *x = NULL;
  list_ele_t *y = q->head;
  list_ele_t *z;

  list_ele_t *tail = q->tail;
  list_ele_t *head = q->head;
  q->tail = head;
  q->head = tail;

  while (y != NULL)
  {
    z = y->next;
    y->next = x;

    x = y;
    y = z;
  }
  /* You need to write the code for this function */
}
