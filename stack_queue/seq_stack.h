#ifndef  SEQ_STACK_H
#define  SEQ_STACK_H

#include  <stdlib.h>
#include  <assert.h>

#define   STACK_SIZE    100

/**< 
 * sequential stack implementation
 *
 * */

/**< seq_stack: the sequential stack definition
 * .st: the stack space
 * .top: the top of the stack
 *
 * */
struct seq_stack {
    int st[STACK_SIZE];
    int top;
};

void seq_stack_init(struct seq_stack **st);
int seq_stack_isempty(const struct seq_stack *st);
int seq_stack_isfull(const struct seq_stack *st);
void seq_stack_push(struct seq_stack *st, int value);
void seq_stack_pop(struct seq_stack *st, int *val);
#endif
