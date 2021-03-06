#ifndef  GENERIC_QUEUE_H
#define  GENERIC_QUEUE_H

#include  <string.h> // for memcpy()
#include  <stdlib.h> // for malloc() and realloc()
#include  <assert.h> // for assert()

#define   MAX_QUEUE_SIZE    100

struct generic_queue
{
    int front;
    int rear;
    int total;
    int element_size;
    void *queue_element;
};

void generic_queue_init(struct generic_queue **qu, const int element_size);
int generic_queue_isempty(const struct generic_queue *qu);
void generic_queue_in(struct generic_queue *qu, const void *entry);
void generic_queue_out(struct generic_queue *qu, void *entry);

#endif  /*GENERIC_QUEUE_H*/
