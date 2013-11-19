#include  "seq_stack.h"

/**< seq_stack_init: initialize the sequential stack
 * @st: the stack to be initialized
 *
 * */
void seq_stack_init(struct seq_stack **st)
{
    *st = malloc(sizeof(struct seq_stack));
    assert(*st);
    (*st)->top = -1;
}

/**< seq_stack_isempty: test if the stack is empty
 * @st: the stack to be tested
 *
 * */
int seq_stack_isempty(const struct seq_stack *st)
{
    assert(st);
    return st->top == -1;
}

/**< seq_stack_isfull: test if the stack is full
 * @st: the stack to be tested
 *
 * */
int seq_stack_isfull(const struct seq_stack *st)
{
    assert(st);
    return st->top == STACK_SIZE - 1;
}

/**< seq_stack_push: push an element into the stack
 * @st: the stack the element to be pushed into
 * @value: the value of the element to be pushed into the stack
 *
 * */
void seq_stack_push(struct seq_stack *st, int value)
{
    assert(st);
    assert(!seq_stack_isfull(st));
    st->top++;
    st->st[st->top] = value;
}

/**< seq_stack_pop: pop the top element from the stack
 * @st: the stack the top element to be popped out
 * @val: the space the popped element to be saved
 *
 * */
void seq_stack_pop(struct seq_stack *st, int *val)
{
    assert(st);
    assert(!seq_stack_isempty(st));
    *val = st->st[st->top--];
}
