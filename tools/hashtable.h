#include  <stdlib.h>
#include  <assert.h>
#include  <string.h>
#include  <stdio.h>

#define   HTSIZE    80
#define   MAGICNO   79

struct hashnode
{
    int key;
    void *value;
    struct hashnode *next;
};

struct hashtable
{
    struct hashnode htable[HTSIZE];
};

int hash(int key);
void htable_init(struct hashtable *ht);
struct hashnode *hashnode_new(int key, void *value);
int htable_add(struct hashtable *ht, struct hashnode *hnode);
int htable_del(struct hashtable *ht, int key, struct hashnode *valptr);
struct hashnode *htable_search(const struct hashtable *ht, int key);
