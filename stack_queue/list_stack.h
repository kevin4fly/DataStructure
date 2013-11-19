#ifndef   LIST_STACK_H
#define   LIST_STACK_H

#include  <stdlib.h> //for malloc()
#include  <stdio.h>  //for printf()
#include  <assert.h> //for assert()

/**< 
 * linked list stack implementation
 *
 * */

/* stack_node: the stack node struct definition
 * .prev: point to the previous node of the linked list stack
 * .key:  the value of the node
 *
 * */
struct stack_node {
    struct stack_node *prev;
    int key;
};

/* list_stack: the linked list stack struct definition
 * .top: point to the top node
 *
 * */
struct list_stack {
    struct stack_node *top;
};

/* LIST_STACK: init the stack via macro
 * @st: the stack to be initialized
 *
 * */
#define   INIT_LIST_STACK(st) { .top = NULL }
#define   LIST_STACK(st) \
          struct list_stack st = INIT_LIST_STACK(st)

void list_stack_init(struct list_stack **st);
struct stack_node *stack_node_new(int val);
int list_stack_isempty(struct list_stack *st);
void do_list_stack_push(struct list_stack *st, struct stack_node *entry);
void list_stack_push(struct list_stack *st, int value);
void do_list_stack_pop(struct list_stack *st);
void list_stack_pop(struct list_stack *st, int *val);
#endif
