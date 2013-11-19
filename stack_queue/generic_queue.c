#include  "generic_queue.h"

/**< generic_queue_init: initialize the generic cyclic queue
 * @qu: the queue to be initialized
 * @element_size: the size of the element of the queue
 *
 * */
void generic_queue_init(struct generic_queue **qu, const int element_size)
{
    (*qu) = malloc(sizeof(struct generic_queue));
    assert(*qu);
    (*qu)->front = 0;
    (*qu)->rear = 0;
    (*qu)->total = MAX_QUEUE_SIZE;
    (*qu)->element_size = element_size;
    (*qu)->queue_element = malloc((*qu)->total*(*qu)->element_size);
    assert((*qu)->queue_element);
}

/**< generic_queue_isempty: test if the generic cyclic queue is empty
 * @qu: the queue to be tested
 *
 * */
int generic_queue_isempty(const struct generic_queue *qu)
{
    assert(qu);
    return qu->front == qu->rear;
}

/**< generic_queue_isfull: test if the generic cyclic queue is full
 *
 * */
int generic_queue_isfull(const struct generic_queue *qu)
{
    assert(qu);
    return (qu->front+1)%qu->total == qu->rear;
}

/**< generic_queue_in: add an element into the generic cyclic queue
 * @qu: the queue the element to be added into
 * @entry: the element to be added
 *
 * */
void generic_queue_in(struct generic_queue *qu, const void *entry)
{
    assert(qu && !generic_queue_isfull(qu));
    void *dest_addr = (char *)qu->queue_element + qu->front * qu->element_size;
    memcpy(dest_addr,entry,qu->element_size);
    qu->front=(qu->front+1)%qu->total;
}

/**< generic_queue_out: delete an element from the generic cyclic queue
 * @qu: the queue the element to be deleted from
 * @entry: the space the deleted element to be saved
 *
 * */
void generic_queue_out(struct generic_queue *qu, void *entry)
{
    assert(qu && !generic_queue_isempty(qu));
    void *src_addr =  (char *)qu->queue_element + qu->element_size * qu->rear;
    memcpy(entry,src_addr,qu->element_size);
    qu->rear=(qu->rear+1)%qu->total;
}
