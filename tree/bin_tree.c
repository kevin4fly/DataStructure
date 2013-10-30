#include  "bin_tree.h"

#include  <stdlib.h> // for malloc();
#include  <assert.h> // for assert();
#include  <stdio.h>  // for printf();

/* bin_tree_node_new: create new binary tree node
 * @val: the value of the new node
 *
 * */
struct bin_tree *bin_tree_node_new(const int val)
{
    struct bin_tree *new = malloc(sizeof(struct bin_tree));
    new->key = val;
    new->lchild = NULL;
    new->rchild = NULL;
    new->parent = NULL;
    new->sibling = NULL;
    return new;
}

/* create_bin_tree_by_bracket:create a binary tree by a string with brackets
 * @root: the root of the tree to be created
 * @elements: the elements to be used to create tree
 *
 *
 * description: if we type this kind of string: A(B(C,D(E,F),G(H,I)), the
 * tree will be built according to it with "A" as its root
 *
 * */
void create_bin_tree_by_bracket(struct bin_tree **root, const char *elements)
{
    struct generic_stack *st = NULL;
    generic_stack_init(&st,sizeof(struct bin_tree *));
    const char *p_char;
    struct bin_tree *new_node = NULL, *temp = NULL;
    int which_child = 0;
    for( p_char=elements ; *p_char ; p_char++ )
    {
        switch ( *p_char )
        {
            case '(' :
                {
                    generic_stack_push(st,&new_node);
                    which_child = 1;
                }
                break;
            case ',' :
                {
                    which_child = 2;
                }
                break;
            case ')' :
                {
                    generic_stack_pop(st,&temp);
                }
                break;
            default :
                {
                    new_node = bin_tree_node_new(*p_char);
                    if( generic_stack_isempty(st) )
                    {
                        *root = new_node;
                    }
                    else
                    {
                        struct bin_tree **parent = generic_stack_gettop(st);
                        new_node->parent = *parent;
                        switch ( which_child )
                        {
                            case 1:
                                {
                                    (*parent)->lchild = new_node;
                                }
                                break;
                            case 2:
                                {
                                    (*parent)->rchild = new_node;
                                }
                                break;
                        }
                    }
                }
                break;
        }
    }
}

/* create_complete_bin_tree: create complete binary tree via string provieded
 * @entrys: the string used to build the tree
 * @cnt: the count of the tree node
 *
 * */
void create_complete_bin_tree(struct bin_tree **root, const char *entrys, const int cnt)
{
    struct generic_queue *qu = NULL;
    generic_queue_init(&qu,sizeof(struct bin_tree *));
    int i = 0, which_child = 0;
    struct bin_tree *out = NULL;
    for( i=0 ; i<cnt ; i++ )
    {
        struct bin_tree *new_node = bin_tree_node_new(entrys[i]);
        if( generic_queue_isempty(qu) )
        {
            *root = new_node;
            generic_queue_in(qu,&new_node);
        }
        else
        {
            if( which_child==0 )
            {
                generic_queue_out(qu,&out);
                out->lchild = new_node;
                which_child = 1;
            }
            else
            {
                out->rchild = new_node;
                which_child = 0;
            }
            new_node->parent = out;
            generic_queue_in(qu,&new_node);
        }
    }
}


/* do_bin_search_tree_add_recursive: do the action to add the new node @entry
 * with recursiveway.
 * @root: the root of the tree the new node to add into
 * @entry: the new node to be added
 *
 * */
void do_bin_search_tree_add_recursive(struct bin_tree **root, struct bin_tree *entry)
{
    if( *root==NULL )
    {
        *root = entry;
        return;
    }
    if( (*root)->key > entry->key )
    {
        do_bin_search_tree_add_recursive(&((*root)->lchild),entry);
    }
    else
    {
        do_bin_search_tree_add_recursive(&((*root)->rchild),entry);
    }
}

/* bin_search_tree_search: search the @key in the tree
 * @root: the root of the tree
 * @key: the key to be searched
 *
 * */
struct bin_tree *bin_search_tree_search(struct bin_tree *root, const int key)
{
    struct bin_tree *p = root;
    while( p!=NULL )
    {
        if( p->key == key )
        {
            return p;
        }
        else if( p->key > key )
        {
            p = p->lchild;
        }
        else
            p = p->rchild;
    }
    return NULL;
}

/* do_bin_search_tree_add_nonrecursive: do the action to add the new node @entry
 * with non-recursive way.
 * @root: the root of the tree the new node to add into
 * @entry: the new node to be added
 *
 * */
void do_bin_search_tree_add_nonrecursive(struct bin_tree **root, struct bin_tree *entry)
{
    struct bin_tree **p = root;
    while( *p!=NULL )
    {
        if( (*p)->key > entry->key )
        {
            p = &((*p)->lchild);
        }
        else
        {
            p = &((*p)->rchild);
        }
    }
    *p = entry;
}


/* bin_search_tree_add: add a new node with value of @element into the tree
 * @root: the root of the tree the new node to add into
 * @element: the value of the new node to be added
 *
 * */
void bin_search_tree_add(struct bin_tree **root, const int element)
{
    struct bin_tree *new_node = bin_tree_node_new(element);
    do_bin_search_tree_add_nonrecursive(root,new_node);
}

/* bin_search_tree_del: delete the node whose key value is equal to @del_key
 * @root: the root of the tree
 * @del_key: the key value of the node to be deleted
 *
 * */
void bin_search_tree_del(struct bin_tree **root, const int del_key)
{
    // cur_del: the node to be deleted
    // cur_parent: the parent of the cur_del that is gonna be deleted
    // cur_child: the child of the cur_del this is gonan be deleted
    struct bin_tree *cur_parent = NULL, *cur = *root;
    struct bin_tree *cur_child = NULL, *cur_del = NULL;
    int flag = 0;
    while( cur != NULL )
    {
        if( cur->key > del_key )
        {
            cur_parent = cur;
            cur = cur->lchild;
        }
        else if( cur->key < del_key )
        {
            cur_parent = cur;
            cur = cur->rchild;
        }
        else
        {
            flag = 1;
            break;
        }
    }
    if( flag )
    {
        cur_del = cur;
        if( cur_del->lchild !=NULL && cur_del->rchild !=NULL )
        {
            cur_parent = cur_del;
            cur_del = cur_del->lchild;
            while( cur_del->rchild != NULL )
            {
                cur_parent = cur_del;
                cur_del = cur_del->rchild;
            }
            cur->key = cur_del->key;
        }
        if( cur_del->rchild == NULL )
        {
            cur_child = cur_del->lchild;
        }
        else
        {
            cur_child = cur_del->rchild;
        }
        if( cur_parent!= NULL )
        {
            if( cur_del == cur_parent->lchild )
            {
                cur_parent->lchild = cur_child;
            }
            else
            {
                cur_parent->rchild = cur_child;
            }
        }
        else
        {
            *root = cur_child;
        }
        free(cur_del);
    }
}

void breadth_traverse_first_bin_tree(const struct bin_tree *root);

void preorder_traverse_bin_tree_recursive(const struct bin_tree *root)
{
    if( root )
    {
        printf("%-5d",root->key);
        preorder_traverse_bin_tree_recursive(root->lchild);
        preorder_traverse_bin_tree_recursive(root->rchild);
    }
}

void preorder_traverse_bin_tree_nonrecursive1(const struct bin_tree *root);
void inorder_traverse_bin_tree_recursive(const struct bin_tree *root)
{
    if( root )
    {
        inorder_traverse_bin_tree_recursive(root->lchild);
        printf("%-5d",root->key);
        inorder_traverse_bin_tree_recursive(root->rchild);
    }
}

void inorder_traverse_bin_tree_nonrecursive1(const struct bin_tree *root);
void postorder_traverse_bin_tree_recursive(const struct bin_tree *root);
void postorder_traverse_bin_tree_nonrecursive1(const struct bin_tree *root);
struct bin_tree *bin_tree_build_by_preorder_inorder_list(const int *preorder,
                                                         const int *inorder,
                                                         const int len);
void get_bin_tree_preorder_list(const struct bin_tree *root, struct generic_queue *qu);
void get_bin_tree_inorder_list(const struct bin_tree *root, struct generic_queue *qu);
void get_bin_tree_postorder_list(const struct bin_tree *root, struct generic_queue *qu);
int is_bin_search_tree_postorder_list(const int *postorder, const int len);
void do_convert(struct bin_tree *root, struct bin_tree **list);
void bin_tree_to_list(struct bin_tree *root);

int bin_tree_total_nodes(const struct bin_tree *root);
int bin_tree_total_leaves(const struct bin_tree *root);
int bin_tree_kth_level_nodes(struct bin_tree *root, const int kth);

int bin_tree_height(const struct bin_tree *root);
int bin_tree_isbalanced(const struct bin_tree *root);
int bin_tree_iscomplete(const struct bin_tree *root);
int bin_tree_isfull(const struct bin_tree *root);
int bin_tree_isequivalent(const struct bin_tree *root);
int bin_tree_ismirrored(const struct bin_tree *root);
int bin_tree_issubtree(const struct bin_tree *root);
int bin_tree_ispart(const struct bin_tree *root1, const struct bin_tree *root2);

void bin_tree_set_parent(struct bin_tree *root);
void bin_tree_set_sibling(struct bin_tree *root);
void bin_tree_traverse_via_sibling(const struct bin_tree *root);

