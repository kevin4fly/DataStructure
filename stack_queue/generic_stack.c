#include  "generic_stack.h"

/* generic_stack_init: initialized the generic stack
 * @st: the stack to be initialized
 * @element_size: the size of the element in the stack
 *
 * */
void generic_stack_init( struct generic_stack **st, const int element_size )
{
    (*st) = malloc(sizeof(struct generic_stack));
    assert(*st);
    (*st)->top = 0;
    (*st)->total = 4;
    (*st)->element_size = element_size;
    (*st)->element_stack = malloc((*st)->total * (*st)->element_size);
    assert((*st)->element_stack);
}

/* generic_stack_isempty: test if the stack is empty
 * @st: the stack to be tested
 *
 * */
int generic_stack_isempty( const struct generic_stack *st )
{
    assert(st);
    return st->top == 0;
}

/* generic_stack_isfull: test if the stack is full
 * @st: the stack to be tested
 *
 * */
static int generic_stack_isfull( const struct generic_stack *st )
{
    return st->top == st->total;
}

/* generic_stack_extend: if the stack is full, extend the stack 2 times
 * @st: the stack to be extended
 *
 * */
static void generic_stack_extend( struct generic_stack *st )
{
    st->total = st->total * 2;
    st->element_stack = realloc(st->element_stack, st->total*st->element_size);
    assert(st->element_stack);
}

/* generic_stack_gettop: return the top element of the stack
 * @st: the stack whose top element will be returned
 *
 * */
void *generic_stack_gettop( const struct generic_stack *st )
{
    assert(st && !generic_stack_isempty(st));
    int top = st->top-1;
    return st->element_stack + st->element_size * top;
}

/* generic_stack_push: push an element into the stack
 * @st: the stack the element to be pushed into
 * @element_entry: the element to be pushed
 *
 * */
void generic_stack_push( struct generic_stack *st, const void *element_entry )
{
    assert(st);
    if( generic_stack_isfull(st) )
    {
        generic_stack_extend(st);
    }
    void *dest_addr = (char *)st->element_stack + st->top * st->element_size;
    memcpy(dest_addr,element_entry,st->element_size);
    st->top++;
}

/* generic_stack_pop: pop the element out of the stack
 * @st: the stack the element to be popped out
 * @element_entry: the space the popped out element to be saved
 *
 * */
void generic_stack_pop( struct generic_stack *st, void *element_entry)
{
    assert(st && !generic_stack_isempty(st));
    st->top--;
    void *src_addr = (char *)st->element_stack + st->top * st->element_size;
    memcpy(element_entry,src_addr,st->element_size);
}
