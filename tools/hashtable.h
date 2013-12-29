#ifndef   HASHTABLE_h
#define   HASHTABLE_h

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <assert.h>

/**< hash table implementation
 *
 *   */

//hash table size
#define   HTSIZE    80
//the magic number for the hash function
#define   MAGICNO   79

/* hashnode: the node pointed by the entries in the hash table
 * .key: to identify the node
 * .value: the value of the node
 * .ref_cnt: to count the reference of the node
 * .next: to point to the next node of the list
 *
 * */
struct hashnode
{
    int key;
    void *value;
    int ref_cnt;
    struct hashnode *next;
};

/* hashtable: the hash table containing the entries pointing to the hash node
 * .htable: to point to the hashnode pointer table
 * .value_free: a callback function used to free the space of hashnode's value
 * member
 *
 * */
struct hashtable
{
    struct hashnode **htable;
    void (*value_free)(void *value);
};

int hash(int key);
void htable_init(struct hashtable **ht, void (*value_free)(void *value));
struct hashnode *hashnode_new(int key, void *value);
void hashnode_free(struct hashtable *ht, struct hashnode *entry);
void htable_add(struct hashtable *ht,int key, void *value);
int htable_del(struct hashtable *ht, int key, struct hashnode *valptr);
struct hashnode *htable_search(const struct hashtable *ht, int key);
void htable_destory(struct hashtable *ht);

#endif
