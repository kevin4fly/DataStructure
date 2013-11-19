#include  "seq_queue.h"

/**< seq_queue_init: initialize the sequential cyclic queue
 * @qu: the queue to be initialized
 *
 * */
void seq_queue_init(struct seq_queue **qu)
{
    *qu = malloc(sizeof(struct seq_queue));
    assert(*qu);
    (*qu)->front = 0;
    (*qu)->rear = 0;
}

/**< seq_queue_isempty: test if the sequential cyclic queue is empty
 * @qu: the queue to be tested
 *
 * */
int seq_queue_isempty(const struct seq_queue *qu)
{
    assert(qu);
    return qu->front == qu->rear;
}

/**< seq_queue_isfull: test if the sequential cyclic queue is full
 * @qu: the queue to be tested
 *
 * */
int seq_queue_isfull(const struct seq_queue *qu)
{
    assert(qu);
    return (qu->front + 1)%QUEUE_SIZE == qu->rear;
}

/**< seq_queue_in: add an element into the sequential cyclic queue
 * @qu: the queue the element to be added into
 * @value: the value of the element to be added
 *
 * */
void seq_queue_in(struct seq_queue *qu, int value)
{
    assert(qu);
    assert(!seq_queue_isfull(qu));
    qu->front = (qu->front+1)%QUEUE_SIZE;
    qu->qu[qu->front] = value;
}

/**< seq_queue_out: delete an element from the sequential cyclic queue
 * @qu: the queue the element to be deleted from
 * @val: the space to save the deleted element
 *
 * */
void seq_queue_out(struct seq_queue *qu, int *val)
{
    assert(qu);
    assert(!seq_queue_isempty(qu));
    qu->rear = (qu->rear+1)%QUEUE_SIZE;
    *val = qu->qu[qu->rear];
}
