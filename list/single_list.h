#ifndef   SINGLE_LIST_H
#define   SINGLE_LIST_H

/**< 
 * Single linked list implementation with list head
 *
 * */

/* slist_node: single linked list struct definition
 * .next: point to the next node of the list
 * .key:  the value of the node
 *
 * */
struct slist_node {
    struct slist_node *next;
    int key;
};

/* SLIST_HEAD: init the list via macro
 * @head: the list head to be initialized
 *
 * */
#define   INIT_SLIST_NODE(head) { .next = NULL }
#define   SLIST_HEAD(head) \
          struct slist_node head = INIT_SLIST_NODE(head)

// basic operation including init,add,delete,traverse of single linked list
void slist_init(struct slist_node **head);
struct slist_node *slist_node_new(int data);
void do_slist_add(struct slist_node *pos, struct slist_node *new);
void slist_add_head(struct slist_node *head, int data);
void slist_add_tail(struct slist_node *head, int data);
struct slist_node *slist_search(struct slist_node *head, int value);
void do_slist_del(struct slist_node *prev, struct slist_node *next);
void slist_del(struct slist_node *head, struct slist_node *del, int *value);
void slist_traverse(struct slist_node *head);

// advance operation of the single linked list
void slist_splice(struct slist_node *position, struct slist_node *list);
void slist_reverse(struct slist_node *head);
const struct slist_node *slist_find_last_kth(const struct slist_node *head, int k);
const struct slist_node *slist_find_mid_node(const struct slist_node *head);
void slist_merge_sorted_list(struct slist_node *list1, struct slist_node *list2);

// the Beauty of Programming
void slist_delete(struct slist_node *entry);
struct slist_node *slist_find_1st_common_node(struct slist_node *list1,
                                              struct slist_node *list2);
struct slist_node *slist_find_last_common_node(struct slist_node *list1,
                                              struct slist_node *list2);
int slist_is_cyclic(const struct slist_node *list);
#endif
