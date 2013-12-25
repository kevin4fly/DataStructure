#include  "hashtable.h"

int hash(int key)
{
    return key % MAGICNO;
}

void htable_init(struct hashtable *ht)
{
    memset(ht,0,sizeof(struct hashtable));
}

struct hashnode *hashnode_new(int key, void *value)
{
    struct hashnode *new = malloc(sizeof(struct hashnode));
    assert(new);
    new->key = key;
    char * value_new = strdup((char*)value);
    assert(value_new);
    new->value = value_new;
    new->next = NULL;
    return new;
}

struct hashnode *htable_search(const struct hashtable *ht, int key)
{
    assert(ht);
    int hash_key = hash(key);
    struct hashnode *p = ht->htable[hash_key].next;
    while( p != NULL )
    {
        if( p->key == key )
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int htable_add(struct hashtable *ht, struct hashnode *hnode)
{
    assert(ht);
    assert(hnode);
    if( htable_search(ht,hnode->key) == NULL )
    {
        int hash_key = hash(hnode->key);
        hnode->next = ht->htable[hash_key].next;
        ht->htable[hash_key].next = hnode;
        return 1;
    }
    else
    {
        printf("key %d already exist, add failed!\n", hnode->key);
        return 0;
    }
}

int htable_del(struct hashtable *ht, int key, struct hashnode *valptr)
{
    assert(ht);
    int hash_key = hash(key);
    struct hashnode *p = &ht->htable[hash_key];
    while( p->next != NULL )
    {
        if( p->next->key == key )
        {
            struct hashnode *del = p->next;
            p->next = del->next;
            if( valptr != NULL )
            {
                *valptr = *del;
            }
            free(del);
            return 1;
        }
        p = p->next;
    }
    printf("key %d does not exist, delete failed!\n", key);
    return 0;
}
