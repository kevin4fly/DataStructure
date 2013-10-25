#ifndef  GENERIC_QUEUE_H
#define  GENERIC_QUEUE_H

#define   MAX_QUEUE_SIZE    10

struct generic_queue
{
    int front;
    int rear;
    int total;
    int element_size;
    void *queue_element;
};

void generic_queue_init(struct generic_queue **qu, int element_size);
int generic_queue_isempty(const struct generic_queue *qu);
void generic_queue_in(struct generic_queue *qu, const void *entry);
void generic_queue_out(struct generic_queue *qu, void *entry);



#endif  /*GENERIC_QUEUE_H*/
