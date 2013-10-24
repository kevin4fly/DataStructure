#include  "list_queue.h"

#include  <stdlib.h> //for malloc()
#include  <stdio.h>  //for printf()
#include  <assert.h> //for assert()

/* list_queue: init the list queue
 * @qu: the queue to be initialized
 *
 * */
void list_queue_init(struct list_queue **qu)
{
    (*qu) = malloc(sizeof(struct list_queue));
    (*qu)->front = NULL;
    (*qu)->front = NULL;
}

/* queue_node_new: create a new queue node
 * @val: the key value of the new node
 *
 * */
struct queue_node *queue_node_new(int val)
{
    struct queue_node *new = malloc(sizeof(struct queue_node));
    assert(new);
    new->key = val;
    new->prev = NULL;
    return new;
}

/* list_queue_isempty: judge if the @qu is empty
 * @qu: the queue to be testified
 *
 * */
int list_queue_isempty(struct list_queue *qu)
{
    assert(qu);
    return qu->front==NULL && qu->rear==NULL;
}

/* do_list_queue_in: do add entry into @qu action
 * @qu: the queue the entry to be added into
 * @entry: the new entry to be added
 *
 * */
void do_list_queue_in(struct list_queue *qu, struct queue_node *entry)
{
    if( list_queue_isempty(qu) )
    {
        qu->front = entry;
        qu->rear = entry;
    }
    else
    {
        qu->front->prev = entry;
        qu->front = entry;
    }
}

/* list_queue_in: add entry into the queue
 * @qu: the queue the entry to be added into
 * @value: the value of the new node
 *
 * */
void list_queue_in(struct list_queue *qu, int value)
{
    assert(qu);
    struct queue_node *entry = queue_node_new(value);
    do_list_queue_in(qu,entry);
}

/* do_list_queue_out: do the list out action
 * @st: the queue to be out
 *
 * */
void do_list_queue_out(struct list_queue *qu)
{
    struct queue_node *entry = qu->rear;
    qu->rear = qu->rear->prev;
    if( qu->rear )
    {
        qu->front = NULL;
    }
    free(entry);
}

/* list_queue_out: delete entry from the queue
 * @qu: the queue the last node to be deleted
 * @val: save the value of the node to be deleted
 *
 * */
void list_queue_out(struct list_queue *qu, int *val)
{
    assert(qu);
    assert(!list_queue_isempty(qu));
    *val = qu->rear->key;
    do_list_queue_out(qu);
}
