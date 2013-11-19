#ifndef  SEQ_QUEUE_H
#define  SEQ_QUEUE_H

#include  <stdlib.h>
#include  <assert.h>

#define   QUEUE_SIZE    100

/**< 
 * sequential cyclic queue implementation
 *
 * */

/**< seq_queue: the sequential cyclic queue definition
 * .qu: the qu space
 * .front: the front of the queue
 * .rear: the rear of the queue
 *
 * */
struct seq_queue {
    int qu[QUEUE_SIZE];
    int front;
    int rear;
};

void seq_queue_init(struct seq_queue **qu);
int seq_queue_isempty(const struct seq_queue *qu);
int seq_queue_isfull(const struct seq_queue *qu);
void seq_queue_in(struct seq_queue *qu, int value);
void seq_queue_out(struct seq_queue *qu, int *val);

#endif  /*SEQ_QUEUE_H*/
