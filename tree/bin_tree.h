#ifndef  BIN_TREE_H
#define  BIN_TREE_H

#include  "../stack_queue/generic_queue.h"
#include  "../stack_queue/generic_stack.h"
#include  "../tools/tools.h"

#include  <stdio.h>
#include  <stdlib.h>
#include  <time.h>

struct bin_tree
{
    int key;
    struct bin_tree *lchild;
    struct bin_tree *rchild;
    struct bin_tree *parent;
    struct bin_tree *sibling;
};

struct bin_tree *bin_tree_node_new(const int val);
void create_bin_tree_by_bracket(struct bin_tree **root, const char *elements);
void create_complete_bin_tree(struct bin_tree **root, const int *entrys, const int cnt);
struct bin_tree *bin_search_tree_search(struct bin_tree *root, const int key);
void do_bin_search_tree_add_recursive(struct bin_tree **root, struct bin_tree *entry);
void do_bin_search_tree_add_nonrecursive(struct bin_tree **root, struct bin_tree *entry);
void bin_search_tree_add(struct bin_tree **root, const int element);
void bin_search_tree_del(struct bin_tree **root, const int del_key);

void breadth_traverse_first_bin_tree(const struct bin_tree *root);
void depth_traverse_first_bin_tree(const struct bin_tree *root);
void preorder_traverse_bin_tree_recursive(const struct bin_tree *root);
void preorder_traverse_bin_tree_nonrecursive(const struct bin_tree *root);
void inorder_traverse_bin_tree_recursive(const struct bin_tree *root);
void inorder_traverse_bin_tree_nonrecursive(const struct bin_tree *root);
void postorder_traverse_bin_tree_recursive(const struct bin_tree *root);
void postorder_traverse_bin_tree_nonrecursive(const struct bin_tree *root);
struct bin_tree *bin_tree_build_by_preorder_inorder_list(const int *preorder, 
                                                         const int *inorder,
                                                         const int len);
void get_bin_tree_preorder_list(const struct bin_tree *root, struct generic_queue *qu);
void get_bin_tree_inorder_list(const struct bin_tree *root, struct generic_queue *qu);
void get_bin_tree_postorder_list(const struct bin_tree *root, struct generic_queue *qu);
int is_bin_search_tree_postorder_list(const int *postorder, const int len);
void do_convert(struct bin_tree *root, struct bin_tree **list);
struct bin_tree *bin_tree_to_list(struct bin_tree *root);

int bin_tree_height(const struct bin_tree *root);
int bin_tree_total_nodes(const struct bin_tree *root);
int bin_tree_total_leaves(const struct bin_tree *root);
int bin_tree_total_nodes_of_kth_level(const struct bin_tree *root, const int kth);
int bin_tree_total_nodes_of_top_nlevel(const struct bin_tree *root, const int top);

int bin_tree_isbalanced(const struct bin_tree *root);
int bin_tree_iscomplete(const struct bin_tree *root);
int bin_tree_isfull(const struct bin_tree *root);
int bin_tree_isequivalent(const struct bin_tree *root1, const struct bin_tree *root2);
int bin_tree_ismirrored(const struct bin_tree *root1, const struct bin_tree *root2);
int bin_tree_issubtree(const struct bin_tree *root1, const struct bin_tree *root2);

void bin_tree_set_parent(struct bin_tree *child, struct bin_tree *parent);
void bin_tree_set_sibling(struct bin_tree *root, struct bin_tree *sibling);
void bin_tree_traverse_via_sibling(const struct bin_tree *root);

#endif  /*BIN_TREE_H*/
