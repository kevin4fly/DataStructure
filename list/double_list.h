#ifndef   DOUBLE_LIST_H
#define   DOUBLE_LIST_H

/**< 
 * double cyclic linked list implementation without list head
 *
 * */

/* dlist_node: double cyclic linked list struct definition
 * .prev: point to the previous node of the node
 * .next: point to the next node of the node
 * .key:  the value of the node
 *
 * */
struct dlist_node {
    struct dlist_node *prev;
    struct dlist_node *next;
    int key;
};

/* dlist_HEAD: init the list via macro
 * @head: the list head to be initialized
 *
 * */
#define   DLIST_INIT_HEAD(head,val) { .prev=&(head), .next=&(head), .key=val }
#define   DLIST_HEAD(head,val) \
                struct dlist_node head = DLIST_INIT_HEAD(head,val)

void dlist_init(struct dlist_node **list, int val);
struct dlist_node *dlist_node_new(int data);
void _dlist_add(struct dlist_node *prev, struct dlist_node *next, struct dlist_node *new);
void dlist_add_head(struct dlist_node *position, int data);
void dlist_add_tail(struct dlist_node *position, int data);
struct dlist_node *dlist_search(struct dlist_node *head, int value);
void _dlist_del(struct dlist_node *prev, struct dlist_node *next);
void dlist_del(struct dlist_node *list, struct dlist_node *entry, int *value);
void dlist_traverse(struct dlist_node *list);

#endif
