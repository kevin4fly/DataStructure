#include  "double_list.h"

#include  <stdlib.h> //for malloc()
#include  <stdio.h>  //for printf()
#include  <assert.h> //for assert()

/* dlist_init: init the list
 * @list: the list to be initialized
 *
 * */
void dlist_init(struct dlist_node **list, int val)
{
    (*list) = malloc(sizeof(struct dlist_node));
    assert(*list);
    (*list)->prev = *list;
    (*list)->next = *list;
    (*list)->key = val;
}

/* dlist_node_new: create a new dlist node
 * @data: the key value of the new node
 *
 * */
struct dlist_node *dlist_node_new(int data)
{
    struct dlist_node *new = malloc(sizeof(struct dlist_node));
    assert(new);
    new->prev = NULL;
    new->next = NULL;
    new->key = data;
    return new;
}

/* _dlist_add: add the node to the list
 * @prev: the node befor the node to be added
 * @next: the node after the node to be added
 * @new: the node to be added
 *
 * */
void _dlist_add(struct dlist_node *prev, struct dlist_node *next, struct dlist_node *new)
{
    prev->next = new;
    new->prev = prev;
    next->prev = new;
    new->next = next;
}

/* dlist_add_head: add the node before the position of the list
 * @data: the data to be added
 *
 * */
void dlist_add_head(struct dlist_node *position, int data)
{
    assert(position);
    struct dlist_node *new = dlist_node_new(data);
    _dlist_add(position->prev,position,new);
}

/* dlist_add_tail: add the node after the position of the list
 * @data: the data to be added
 *
 * */
void dlist_add_tail(struct dlist_node *position, int data)
{
    assert(position);
    struct dlist_node *new = dlist_node_new(data);
    _dlist_add(position,position->next,new);
}

/* dlist_search: search the node whose key equals to value
 * @value: the value to be searched
 *
 * */
struct dlist_node *dlist_search(struct dlist_node *list, int value)
{
    assert(list);
    struct dlist_node *p = list;
    do{
        if( p->key==value )
        {
            return p;
        }
        p=p->next;
    }
    while( p!=list );
    return NULL;
}


/* _dlist_del: do delete action
 * prev: the previous node of the node to be deleted
 * next: the next node of the node to deleted
 *
 * */
void _dlist_del(struct dlist_node *prev, struct dlist_node *next)
{
    struct dlist_node *del = prev->next;
    prev->next = next;
    next->prev = prev;
    free(del);
}

/* dlist_del: delete the del node from the list
 * @list: the list the entry attached
 * @del:  the node to be deleted
 * @value: the value of the node to be deleted
 *
 * */
void dlist_del(struct dlist_node *list, struct dlist_node *entry, int *value)
{
    assert(list);
    struct dlist_node *del = dlist_search(list,entry->key);
    if( del )
    {
        *value = del->key;
        _dlist_del(del->prev, del->next);
    }
}

/* dlist_traverse: display the whole node of the list head
 * @head: the list head
 *
 * */
void dlist_traverse(struct dlist_node *list)
{
    assert(list);
    struct dlist_node *p = list;
    do{
        printf("%-5d",p->key);
        p=p->next;
    }while(p!=list);
    printf("\n");
}
