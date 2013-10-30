#include  "generic_queue.h"

#include  <string.h> // for memcpy()
#include  <stdlib.h> // for malloc() and realloc()
#include  <assert.h> // for assert()

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

int generic_queue_isempty(const struct generic_queue *qu)
{
    assert(qu);
    return qu->front == qu->rear;
}

int generic_queue_isfull(const struct generic_queue *qu)
{
    assert(qu);
    return (qu->front+1)%qu->total == qu->rear;
}

void generic_queue_in(struct generic_queue *qu, const void *entry)
{
    assert(qu && !generic_queue_isfull(qu));
    void *dest_addr = (char *)qu->queue_element + qu->front * qu->element_size;
    memcpy(dest_addr,entry,qu->element_size);
    qu->front=(qu->front+1)%qu->total;
}
void generic_queue_out(struct generic_queue *qu, void *entry)
{
    assert(qu && !generic_queue_isempty(qu));
    void *src_addr =  (char *)qu->queue_element + qu->element_size * qu->rear;
    memcpy(entry,src_addr,qu->element_size);
    qu->rear=(qu->rear+1)%qu->total;
}
