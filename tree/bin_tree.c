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
void create_complete_bin_tree(struct bin_tree **root, const int *entrys, const int cnt)
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

/* description: Generally, the methods for the breadth first and depth first
 * search for the tree is incorporated from the graph.
 * BFS: utilize the queue to store all the nodes adjacent with the current node
 * DFS: utilize the stack to store the only one node connected with the
 * current node, and then to the deeper place.
 *
 * */

/* breadth_traverse_first_bin_tree: the breadth first search for the binary tree
 * @root: the root of the tree to be searched
 *
 * */
void breadth_traverse_first_bin_tree(const struct bin_tree *root)
{
    struct generic_queue *qu = NULL;
    struct bin_tree *buffer = NULL;
    generic_queue_init(&qu,sizeof(struct bin_tree *));
    generic_queue_in(qu,&root);
    while( !generic_queue_isempty(qu) )
    {
        generic_queue_out(qu,&buffer);
        if( buffer != NULL )
        {
            printf("%-5d",buffer->key);
            if( buffer->rchild )
            {
                generic_queue_in(qu,&buffer->rchild);
            }
            if( buffer->lchild )
            {
                generic_queue_in(qu,&buffer->lchild);
            }
        }
    }
}

/* depth_traverse_first_bin_tree: the depth first search for the binary tree.
 * Actually, it is also a kind of preorder search for the tree
 * @root: the root of the tree to be searched
 *
 * */
void depth_traverse_first_bin_tree(const struct bin_tree *root)
{
    struct generic_stack *st = NULL;
    struct bin_tree *buffer = NULL;
    generic_stack_init(&st,sizeof(struct bin_tree *));
    generic_stack_push(st,&root);
    while( !generic_stack_isempty(st) )
    {
        generic_stack_pop(st,&buffer);
        if( buffer != NULL )
        {
            printf("%-5d",buffer->key);
            generic_stack_push(st,&buffer->rchild);
            generic_stack_push(st,&buffer->lchild);
        }
    }
}

/* preorder_traverse_bin_tree_recursive: the preorder traverse the binary tree
 * with recursive way.
 * @root: the root of tree to be searched
 *
 * */
void preorder_traverse_bin_tree_recursive(const struct bin_tree *root)
{
    if( root )
    {
        printf("%-5d",root->key);
        preorder_traverse_bin_tree_recursive(root->lchild);
        preorder_traverse_bin_tree_recursive(root->rchild);
    }
}

/* preorder_traverse_bin_tree_nonrecursive: the preorder traverse the binary tree
 * with non-recursive way.
 * @root: the root of tree to be searched
 *
 * description: Actually, depth_traverse_first_bin_tree located in line 317 is
 * a kind of preorder_traverse as well.
 *
 * */
void preorder_traverse_bin_tree_nonrecursive(const struct bin_tree *root)
{
    struct generic_stack *st = NULL;
    generic_stack_init(&st,sizeof(struct bin_tree *));
    const struct bin_tree *buffer = root;
    while( buffer != NULL || !generic_stack_isempty(st) )
    {
        while( buffer != NULL )
        {
            printf("%-5d",buffer->key);
            generic_stack_push(st,&buffer);
            buffer = buffer->lchild;
        }
        // this if statement can be removed, but in order to consistent with the outer
        // while loop's contition, remain it here.
        if( !generic_stack_isempty(st) )
        {
            generic_stack_pop(st,&buffer);
            buffer = buffer->rchild;
        }
    }
}

/* inorder_traverse_bin_tree_recursive: the inorder traverse the binary tree
 * with recursive way.
 * @root: the root of tree to be searched
 *
 * */
void inorder_traverse_bin_tree_recursive(const struct bin_tree *root)
{
    if( root )
    {
        inorder_traverse_bin_tree_recursive(root->lchild);
        printf("%-5d",root->key);
        inorder_traverse_bin_tree_recursive(root->rchild);
    }
}


/* inorder_traverse_bin_tree_nonrecursive: the inorder traverse the binary tree
 * with non-recursive way.
 * @root: the root of tree to be searched
 *
 **/
void inorder_traverse_bin_tree_nonrecursive(const struct bin_tree *root)
{
    struct generic_stack *st = NULL;
    generic_stack_init(&st,sizeof(struct bin_tree *));
    const struct bin_tree *buffer = root;
    while( buffer != NULL || !generic_stack_isempty(st) )
    {
        while( buffer != NULL )
        {
            generic_stack_push(st,&buffer);
            buffer = buffer->lchild;
        }
        if( !generic_stack_isempty(st) )
        {
            generic_stack_pop(st,&buffer);
            printf("%-5d",buffer->key);
            buffer = buffer->rchild;
        }
    }
}

/* postorder_traverse_bin_tree_recursive: the postorder traverse the binary
 * tree
 * @root: the root of the tree to be searched
 *
 * */
void postorder_traverse_bin_tree_recursive(const struct bin_tree *root)
{
    if( root )
    {
        postorder_traverse_bin_tree_recursive(root->lchild);
        postorder_traverse_bin_tree_recursive(root->rchild);
        printf("%-5d",root->key);
    }
}

/* postorder_traverse_bin_tree_nonrecursive: the postorder traverse the binary tree
 * with non-recursive way.
 * @root: the root of tree to be searched
 *
 **/
void postorder_traverse_bin_tree_nonrecursive(const struct bin_tree *root)
{
    struct generic_stack *st = NULL;
    generic_stack_init(&st,sizeof(struct bin_tree *));
    struct bin_tree *pre_buffer = NULL;
    generic_stack_push(st,&root);
    while( !generic_stack_isempty(st) )
    {
        struct bin_tree **p = generic_stack_gettop(st);
        struct bin_tree *buffer = *p;
        if((buffer->lchild == NULL && buffer->rchild == NULL) ||
          ((pre_buffer != NULL) && (pre_buffer==buffer->rchild || pre_buffer==buffer->lchild)))
        {
            printf("%-5d", buffer->key);
            generic_stack_pop(st,&pre_buffer);
        }
        else
        {
            if( buffer->rchild != NULL )
            {
                generic_stack_push(st,&buffer->rchild);
            }
            if( buffer->lchild != NULL )
            {
                generic_stack_push(st,&buffer->lchild);
            }
        }
    }
}


struct bin_tree *bin_tree_build_by_preorder_inorder_list(const int *preorder,
                                                         const int *inorder,
                                                         const int len);

/* get_bin_tree_preorder_list: get the preorder list of tree @root into queue
 * @qu
 * @root: the root of the tree to obtain the preorder list
 * @qu: the queue to store the preorder list
 *
 * */
void get_bin_tree_preorder_list(const struct bin_tree *root, struct generic_queue *qu)
{
    if( root )
    {
        generic_queue_in(qu,&root->key);
        get_bin_tree_preorder_list(root->lchild,qu);
        get_bin_tree_preorder_list(root->rchild,qu);
    }
}

/* get_bin_tree_inorder_list: get the inorder list of tree @root into queue
 * @qu
 * @root: the root of the tree to obtain the inorder list
 * @qu: the queue to store the inorder list
 *
 * */
void get_bin_tree_inorder_list(const struct bin_tree *root, struct generic_queue *qu)
{
    if( root )
    {
        get_bin_tree_inorder_list(root->lchild,qu);
        generic_queue_in(qu,&root->key);
        get_bin_tree_inorder_list(root->rchild,qu);
    }
}

/* get_bin_tree_postorder_list: get the postorder list of tree @root into queue
 * @qu
 * @root: the root of the tree to obtain the postorder list
 * @qu: the queue to store the postorder list
 *
 * */
void get_bin_tree_postorder_list(const struct bin_tree *root, struct generic_queue *qu)
{
    if( root )
    {
        get_bin_tree_postorder_list(root->lchild,qu);
        get_bin_tree_postorder_list(root->rchild,qu);
        generic_queue_in(qu,&root->key);
    }
}

/* is_bin_search_tree_postorder_list: test if array is a postorder list of the
 * tree
 * @postorder: the array of the postorder to be tested
 * @len: the length of the array
 *
 * */
int is_bin_search_tree_postorder_list(const int *postorder, const int len)
{
    if( postorder == NULL )
    {
        return 1;
    }
    if( len==0 || len==1 )
    {
        return 1;
    }
    int mid, right;
    for( mid=0 ; mid<len-1 ; mid++ )
    {
        if( postorder[mid]>postorder[len-1] )
        {
            break;
        }
    }
    for( right = mid+1 ; right<len-1 ; right++ )
    {
        if( postorder[right]<postorder[len-1] )
        {
            return 0;
        }
    }
    return is_bin_search_tree_postorder_list(postorder,mid) &&
           is_bin_search_tree_postorder_list(postorder+mid, len-mid-1);
}
void do_convert(struct bin_tree *root, struct bin_tree **list);
void bin_tree_to_list(struct bin_tree *root);

/* bin_tree_height: the height of the tree
 * @root: the root of the tree
 *
 * */
int bin_tree_height(const struct bin_tree *root)
{
    if( root == NULL )
    {
        return 0;
    }
    return MAX(bin_tree_height(root->lchild), bin_tree_height(root->rchild))
           + 1;
}

/* bin_tree_total_nodes: get the total nodes of the tree
 * @root: the root of the tree
 *
 * */
int bin_tree_total_nodes(const struct bin_tree *root)
{
    if( root == NULL )
    {
        return 0;
    }
    return bin_tree_total_nodes(root->lchild) +
           bin_tree_total_nodes(root->rchild) + 1;
}

/* bin_tree_total_leaves: get the total leaves node of the tree
 * @root: the root of the tree
 *
 * */
int bin_tree_total_leaves(const struct bin_tree *root)
{
    if( root == NULL )
    {
        return 0;
    }
    if( root->lchild == NULL && root->rchild == NULL )
    {
        return 1;
    }
    return bin_tree_total_leaves(root->lchild) +
           bin_tree_total_leaves(root->rchild);
}

/* bin_tree_kth_level_nodes: the total nodes of the kth level of the tree
 * @root: the root of the tree
 *
 * description: if kth < 1, return 0,
 *              if kth > the height of the tree, return the total nodes of the
 *              last level of the tree.
 * (this cannot implement right now, comment it out from line 379 to 382)
 * */
int bin_tree_total_nodes_of_kth_level(const struct bin_tree *root,
                                      const int kth)
{
    if( kth < 1 || root==NULL )
    {
        return 0;
    }
    //if( kth > bin_tree_height(root) )
    //{
    //    return bin_tree_total_nodes_of_kth_level(root,bin_tree_height(root));
    //}
    if( kth == 1 )
    {
        return 1;
    }
    return bin_tree_total_nodes_of_kth_level(root->lchild,kth-1) +
        bin_tree_total_nodes_of_kth_level(root->rchild,kth-1);
}

/* bin_tree_total_nodes_of_topn: the total nodes of the top n level of the
 * tree
 * @root: the root of the tree
 * @top: the top level of the tree
 *
 * description: if top < 0, return 0,
 *              if top > the height of the tree, return the totals nodes of
 *              the tree.
 * */
int bin_tree_total_nodes_of_top_nlevel(const struct bin_tree *root,
                                       const int top)
{
    if( top<1 )
    {
        return 0;
    }
    if( top > bin_tree_height(root) )
    {
        return bin_tree_total_nodes(root);
    }
    if( top == 1 )
    {
        return 1;
    }
    return bin_tree_total_nodes_of_top_nlevel(root->lchild,top-1) +
        bin_tree_total_nodes_of_top_nlevel(root->rchild,top-1) + 1;
}

/* bin_tree_isbalanced: test if the tree is balanced, which means the delta
 * height between each left and right child of the tree only up to 1.
 * Otherwise, it is unbalanced.
 * @root: the root of the tree
 *
 * */
int bin_tree_isbalanced(const struct bin_tree *root)
{
    if( root == NULL )
    {
        return 1;
    }
    if( abs_int(bin_tree_height(root->lchild),bin_tree_height(root->rchild))>1 )
    {
        return 0;
    }
    return bin_tree_isbalanced(root->lchild)&&bin_tree_isbalanced(root->rchild);
}

/* bin_tree_iscomplete: test if the tree is a complete tree
 * @root: the root of the tree
 *
 * */
int bin_tree_iscomplete(const struct bin_tree *root)
{
    struct generic_queue *qu = NULL;
    struct bin_tree *buffer = NULL;
    generic_queue_init(&qu,sizeof(struct bin_tree *));
    generic_queue_in(qu,&root);
    while( !generic_queue_isempty(qu) )
    {
        generic_queue_out(qu,&buffer);
        if( buffer!=NULL )
        {
            generic_queue_in(qu,&(buffer->lchild));
            generic_queue_in(qu,&(buffer->rchild));
        }
        else
        {
            while( !generic_queue_isempty(qu) )
            {
                generic_queue_out(qu,&buffer);
                if( buffer!=NULL )
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

/* bin_tree_isfull: test if the tree is a full tree
 * @root: the root of the tree
 *
 * */
int bin_tree_isfull(const struct bin_tree *root)
{
    if( root == NULL )
    {
        return 1;
    }
    if( bin_tree_height(root->lchild) != bin_tree_height(root->rchild) )
    {
        return 0;
    }
    return bin_tree_isfull(root->lchild) && bin_tree_isfull(root->rchild);
}


/* bin_tree_isequivalent: test if root1 and root2 are equal to each other
 * @root1: the root of tree1
 * @root2: the root of the other tree2
 *
 * */
int bin_tree_isequivalent(const struct bin_tree *root1, const struct bin_tree *root2)
{
    if( root1==NULL && root2==NULL )
    {
        return 1;
    }
    if( root1 == NULL || root2 == NULL )
    {
        return 0;
    }
    if( root1->key != root2->key )
    {
        return 0;
    }
    return bin_tree_isequivalent(root1->lchild,root2->lchild)&&
           bin_tree_isequivalent(root1->rchild,root2->rchild);
}

/* bin_tree_ismirrored: test if root1 mirros root2
 * @root1: the root of one tree
 * @root2: the root of the other tree
 *
 * */
int bin_tree_ismirrored(const struct bin_tree *root1, const struct bin_tree *root2)
{
    if( root1==NULL && root2==NULL )
    {
        return 1;
    }
    if( root1 == NULL || root2 == NULL )
    {
        return 0;
    }
    if( root1->key != root2->key )
    {
        return 0;
    }
    return bin_tree_ismirrored(root1->lchild,root2->rchild) &&
           bin_tree_ismirrored(root1->rchild,root2->lchild);
}

/* bin_tree_issubtree: test if @root2 is the subtree of root1
 * @root1: the root of one tree
 * @root2: the root of the other tree
 *
 * */
int bin_tree_issubtree(const struct bin_tree *root1, const struct bin_tree *root2)
{
    if( root2 == NULL )
    {
        return 1;
    }
    if( root1 == NULL )
    {
        return 0;
    }
    if( root1->key != root2->key )
    {
        return 0;
    }
    return bin_tree_issubtree(root1->lchild,root2->lchild) &&
           bin_tree_issubtree(root1->rchild,root2->rchild);
}

/* bin_tree_set_parent: set the parent for all the nodes of the tree
 * @children: the root of the subtree
 * @parent: the parent of the @child
 *
 * description: the invocation should be bin_tree_set_parent(NULL, root).
 * @root is root of the tree to be set, NULL is, of course, the parent node of
 * the root.
 *
 * */
void bin_tree_set_parent(struct bin_tree *child, struct bin_tree *parent)
{
    if( child)
    {
        child->parent = parent;
        bin_tree_set_parent(child->lchild,child);
        bin_tree_set_parent(child->rchild,child);
    }
}

/* bin_tree_set_sibling: set the sibling for each node of the binary tree
 * @root: the root of the tree the sibling to be set
 * @sibling: the sibling of the root
 *
 * */
void bin_tree_set_sibling(struct bin_tree *root, struct bin_tree *sibling)
{
    if( root==NULL )
    {
        return;
    }
    root->sibling = sibling;
    while( sibling != NULL )
    {
        if( sibling->lchild != NULL )
        {
            sibling = sibling->lchild;
            break;
        }
        if( sibling->rchild != NULL )
        {
            sibling = sibling->rchild;
            break;
        }
        sibling = sibling->sibling;
    }
    if( root->rchild != NULL )
    {
        bin_tree_set_sibling(root->rchild,sibling);
        sibling = root->rchild;
    }
    if( root->lchild != NULL )
    {
        bin_tree_set_sibling(root->lchild,sibling);
    }
}

/* bin_tree_traverse_via_sibling: traverse the binary with sibling
 * @root: the root of the tree to be traversed
 *
 * */
void bin_tree_traverse_via_sibling(const struct bin_tree *root)
{
    const struct bin_tree *cur = root;
    const struct bin_tree *cur_sibling = cur->sibling;
    while( cur != NULL )
    {
        printf("%-5d",cur->key);
        while( cur_sibling != NULL )
        {
            printf("%-5d",cur_sibling->key);
            cur_sibling = cur_sibling->sibling;
        }
        puts("");
        while( cur != NULL )
        {
            if( cur->lchild != NULL )
            {
                cur = cur->lchild;
                cur_sibling = cur->sibling;
                break;
            }
            else if( cur->rchild != NULL )
            {
                cur = cur->rchild;
                cur_sibling = cur->sibling;
                break;
            }
            else
                cur = cur->sibling;
        }
    }
}
