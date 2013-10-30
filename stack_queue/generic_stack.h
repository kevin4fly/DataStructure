#ifndef  GENERIC_STACK_H
#define  GENERIC_STACK_H

struct generic_stack
{
    int total;
    int top;
    int element_size;
    void *element_stack;
};

void generic_stack_init( struct generic_stack **st, const int element_size );
int generic_stack_isempty( const struct generic_stack *st );
void *generic_stack_gettop( const struct generic_stack *st );
void generic_stack_push( struct generic_stack *st, const void *element_entry );
void generic_stack_pop( struct generic_stack *st, void *element_entry);



#endif  /*GENERICSTACK_H*/
