#ifndef   LIST_QUEUE_H
#define   LIST_QUEUE_H

#include  <stdlib.h> //for malloc()
#include  <stdio.h>  //for printf()
#include  <assert.h> //for assert()

/**< 
 * linked list queue implementation
 *
 * */

/* queue_node: the queue node struct definition
 * .prev: point to the prev node of the linked list queue
 * .key:  the value of the node
 *
 * */
struct queue_node {
    struct queue_node *prev;
    int key;
};

/* list_queue: the linked list queue struct definition
 * .top: point to the top node
 *
 * */
struct list_queue {
    struct queue_node *front;
    struct queue_node *rear;
};

/* LIST_QUEUE: init the queue via macro
 * @st: the queue to be initialized
 *
 * */
#define   INIT_LIST_QUEUE(st) { .front = NULL, .rear = NULL }
#define   LIST_QUEUE(qu) \
          struct list_queue qu = INIT_LIST_QUEUE(qu)

void list_queue_init(struct list_queue **qu);
struct queue_node *queue_node_new(int val);
int list_queue_isempty(struct list_queue *qu);
void do_list_queue_in(struct list_queue *st, struct queue_node *entry);
void list_queue_in(struct list_queue *qu, int value);
void do_list_queue_out(struct list_queue *st);
void list_queue_out(struct list_queue *qu, int *val);
#endif
