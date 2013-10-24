#include  "single_list.h"
#include  <stdlib.h> //for malloc()
#include  <stdio.h>  //for printf()
#include  <assert.h> //for assert()

/* slist_init: init the list
 * @head: the list head to be initialized
 *
 * */
void slist_init(struct slist_node **head)
{
    *head = malloc(sizeof(struct slist_node));
    assert(*head);
    (*head)->next = NULL;
}

/* slist_node_new: create a new slist node
 * @data: the key value of the new node
 *
 * */
struct slist_node *slist_node_new(int data)
{
    struct slist_node *new = malloc(sizeof(struct slist_node));
    assert(new);
    new->key = data;
    new->next = NULL;
    return new;
}
/* do_slist_add: add the node to the list
 * @pos: the new node will be added after the pos
 * @new: the node to be added
 *
 * */
void do_slist_add(struct slist_node *pos, struct slist_node *new)
{
    new->next = pos->next;
    pos->next = new;
}

/* slist_add_head: add the node after the head of the list
 * @data: the data to be added
 *
 * */
void slist_add_head(struct slist_node *head, int data)
{
    assert(head);
    struct slist_node *new = slist_node_new(data);
    do_slist_add(head,new);
}

/* slist_add_tail: add the node after the tail of the list
 * @data: the data to be added
 *
 * */
void slist_add_tail(struct slist_node *head, int data)
{
    assert(head);
    struct slist_node *new = slist_node_new(data);
    struct slist_node *p = head;
    while( p->next!=NULL )
    {
        p=p->next;
    }
    do_slist_add(p,new);
}

/* slist_search: search the node whose key equals to value
 * @value: the value to be searched
 *
 * */
struct slist_node *slist_search(struct slist_node *head, int value)
{
    assert(head);
    struct slist_node *p = head->next;
    while( p!=NULL )
    {
        if( p->key == value )
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

/* do_slist_del: do delete action
 * prev: the previous node of the node to be deleted
 * next: the next node of the node to deleted
 *
 * */
void do_slist_del(struct slist_node *prev, struct slist_node *next)
{
    struct slist_node *del = prev->next;
    prev->next = next;
    free(del);
}

/* slist_del: delete the del node from the list
 * @head: the list head
 * @del:  the node to be deleted
 * @value: save the value of the node to be deleted
 *
 * */
void slist_del(struct slist_node *head, struct slist_node *del, int *value)
{
    assert(head);
    struct slist_node *p = head;
    while( p->next!=NULL )
    {
        if( p->next->key==del->key )
        {
            *value = del->key;
            do_slist_del(p,p->next->next);
        }
        p=p->next;
    }
}

/* slist_traverse: display the whole node of the list head
 * @head: the list head
 *
 * */
void slist_traverse(struct slist_node *head)
{
    assert(head);
    struct slist_node *p = head->next;
    while( p!=NULL )
    {
        printf("%-5d",p->key);
        p=p->next;
    }
    printf("\n");
}

/* slist_splice: attach the @list right after the @position
 * @position: the position to be attached after
 * @list: the list to be attached
 *
 * */
void slist_splice(struct slist_node *position, struct slist_node *list)
{
    if( position==NULL || list==NULL || list->next==NULL )
    {
        return;
    }
    struct slist_node *head_list = list->next, *tail_list = head_list;
    while( tail_list->next!=NULL )
    {
        tail_list = tail_list->next;
    }
    tail_list->next=position->next;
    position->next=head_list;
}


/* slist_reverse: reverse the list
 * @head: the head of the list
 *
 * */
void slist_reverse(struct slist_node *head)
{
    assert(head);
    if( head->next==NULL)
    {
        return;
    }
    struct slist_node *p = head->next->next;
    head->next->next=NULL;
    while( p!=NULL )
    {
        struct slist_node *p_next = p->next;
        do_slist_add(head,p);
        p=p_next;
    }
}

/* slist_find_last_kth: find the last kth node of the list
 * @head: the list head
 * description: this function is able to implement it just scanning the list once
 *
 * */
const struct slist_node *slist_find_last_kth(const struct slist_node *head, int k)
{
    assert(head);
    const struct slist_node *p = head, *q = p;
    while( k>0 )
    {
        p=p->next;
        if( p==NULL )
        {
            return NULL;
        }
        k--;
    }
    while( p!=NULL )
    {
        p=p->next;
        q=q->next;
    }
    return q;
}

/* slist_find_mid_node: find the middle node of the @head
 * @head: the list head
 *
 * */
const struct slist_node *slist_find_mid_node(const struct slist_node *head)
{
    assert(head);
    const struct slist_node *p = head, *q = p;
    while( q!=NULL && q->next!=NULL )
    {
        p=p->next;
        q=q->next->next;
    }
    return p;
}


/* slist_merge_sorted_list: the @list1 and @list2 are sorted list, we merge
 * these two sorted lists into @list1
 * @list1: sorted list1
 * @list2: sorted list2
 *
 * */

void slist_merge_sorted_list(struct slist_node *list1,
                             struct slist_node *list2)
{
    assert(list1);
    assert(list2);
    struct slist_node *p_list1 = list1, *p_list2 = list2->next;
    while( p_list1->next!=NULL && p_list2!=NULL )
    {
        if( p_list2->key < p_list1->next->key )
        {
            struct slist_node *t = p_list2->next;
            do_slist_add(p_list1,p_list2);
            p_list2 = t;
        }
        else
            p_list1 = p_list1->next;
    }
    if( p_list1->next == NULL )
    {
        p_list1->next = p_list2;
    }
}

/* slist_delete: delete the @entry in O(1) when @entry is not the head and tail node
 * @entry: the node to be delete
 *
 * */
void slist_delete(struct slist_node *entry)
{
    assert(entry);
    struct slist_node *del = entry->next;
    entry->key = del->key;
    entry->next = del->next;
    free(del);
}

/* slist_find_1st_common_node: the @list1 and @list2 are connected like "Y",
 * the function is to find the 1st common node of them
 * @list1: the head of list1
 * @list2: the head of list2
 *
 * */
struct slist_node *slist_find_1st_common_node(struct slist_node *list1,
                                              struct slist_node *list2)
{
    assert(list1!=NULL && list2!=NULL);
    struct slist_node *p_list1 = list1->next, *p_list2 = list2->next;
    int i=0,j=0;
    while( p_list1!=NULL )
    {
        i++;
        p_list1=p_list1->next;
    }
    while( p_list2!=NULL )
    {
        j++;
        p_list2=p_list2->next;
    }
    p_list1 = list1->next, p_list2 = list2->next;
    while( i>j )
    {
        p_list1 = p_list1->next;
        i--;
    }
    while( j>i )
    {
        p_list2 = p_list2->next;
        j--;
    }
    while( p_list1 && p_list1!=p_list2 )
    {
        p_list1=p_list1->next;
        p_list2=p_list2->next;
    }
    return p_list1;
}

/* slist_find_last_common_node: this function is also used to judge if the
 * @list1 and @list2 are crossed
 * @list1: the head of list1
 * @list2: the head of list2
 *
 * description: we just need to judge if the last node of @list1 and @list2
 * are the same node
 *
 * */
struct slist_node *slist_find_last_common_node(struct slist_node *list1,
                                              struct slist_node *list2)
{
    assert(list1&&list2);
    struct slist_node *p_list1 = list1, *p_list2 = list2;
    while( p_list1->next )
    {
        p_list1=p_list1->next;
    }
    while( p_list2->next )
    {
        p_list2=p_list2->next;
    }
    if( p_list1==p_list2)
    {
        return p_list1;
    }
    return NULL;
}

/* slist_is_cyclic: judge if the @list is cyclic
 * @list: the list head
 *
 * description: let the fast the slow pointer point to the list head, fast pointer moves 2 steps
 * while slow moves 1 steps.Thus, if the cyclic exists, fast and slow will meet with each other,
 * otherwise, fast equals to NULL
 *
 * */
int slist_is_cyclic(const struct slist_node *list)
{
    assert(list);
    const struct slist_node *fast = list->next, *slow = fast;
    while( fast!=NULL && fast->next!=NULL )
    {
        slow = slow->next;
        fast = fast->next->next;
        if( fast !=NULL && (fast==slow || fast->next==slow ))
        {
            return 1;
        }
    }
    return 0;
}
