#include  "list_stack.h"
#include  <stdlib.h> //for malloc()
#include  <stdio.h>  //for printf()
#include  <assert.h> //for assert()

/* list_stack_init: init the list stack @st
 * @st: the stack to be initialized
 *
 * */
void list_stack_init(struct list_stack **st)
{
    (*st) = malloc(sizeof(struct list_stack));
    (*st)->top = NULL;
}

/* list_node_new: create a new stack node
 * @val: the value to be created
 *
 * */
struct stack_node *stack_node_new(int val)
{
    struct stack_node *new = malloc(sizeof(struct stack_node));
    assert(new);
    new->prev = NULL;
    new->key = val;
    return new;
}

/* list_stack_isempty: judge the stack if it is empty or not
 * @st: the stack to be judged
 *
 * */
int list_stack_isempty(struct list_stack *st)
{
    assert(st);
    return st->top == NULL;
}

/* do_list_stack_push: push the @entry into the stack @st
 * @st: the stack the entry to be pushed into
 * @entry: the entry to be pushed
 *
 * */
void do_list_stack_push(struct list_stack *st, struct stack_node *entry)
{
    entry->prev = st->top;
    st->top = entry;
}

/* list_stack_push: do the preparation for the push action
 * @st: the stack the entry to be pushed into
 * @value: the value to be pushed
 *
 * */
void list_stack_push(struct list_stack *st, int value)
{
    assert(st);
    struct stack_node *new = stack_node_new(value);
    do_list_stack_push(st, new);
}

void do_list_stack_pop(struct list_stack *st)
{
    struct stack_node *del = st->top;
    st->top = del->prev;
    free(del);
}

/* list_stack_pop: do the preparation for the pop action
 * @st: the stack whose top will be popped out
 * @val: save the top value
 *
 * */
void list_stack_pop(struct list_stack *st, int *val)
{
    assert(st);
    assert(!list_stack_isempty(st));
    *val = st->top->key;
    do_list_stack_pop(st);
}
