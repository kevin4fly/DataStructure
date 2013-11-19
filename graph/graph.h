#ifndef  GRAPH_H
#define  GRAPH_H

#include  <stdio.h>
#include  <stdlib.h>
#include  <assert.h>
#include  <string.h>
#include  "../tools/tools.h"
#include  "../stack_queue/generic_queue.h"
#include  "../stack_queue/seq_queue.h"
#include  "../stack_queue/generic_stack.h"
#include  "../stack_queue/seq_stack.h"

/**< graphic implementation with adjacent list way */

#define   boolean    int
#define   true       1
#define   false      0

//total numbers of graphic nodes
#define   MAX_GNODES 10

/**< vertex_node: the vertex node struct definition
 * .key: the value of the node
 * .next: point to the next adjacent vertex node
 *
 * */
struct vertex_node
{
    int key;
    struct vertex_node *next;
};

/**< adj_list_graph: the adjacent list graph struct definition
 * .vertics: total vertics of the graph
 *
 * */
struct adj_list_graph
{
    struct vertex_node vertics[MAX_GNODES];
};

struct vertex_node *vertex_node_new(const int key);
void adj_list_graph_init(struct adj_list_graph **g);

boolean adj_list_graph_add_edge(struct adj_list_graph *g, const int start, const int end);
boolean adj_list_graph_dadd_edge(struct adj_list_graph *g, const int start, const int end);
boolean adj_list_graph_del_edge(struct adj_list_graph *g, const int start, const int end);
boolean adj_list_graph_ddel_edge(struct adj_list_graph *g, const int start, const int end);

void adj_list_graph_display(const struct adj_list_graph *g);
void adj_list_graph_BFS_visit(const struct adj_list_graph *g, const struct vertex_node *vnode);
void adj_list_graph_DFS_recursive(const struct adj_list_graph *g, const struct vertex_node *vnode);
void adj_list_graph_DFS_nonrecursive(const struct adj_list_graph *g, const struct vertex_node *vnode);
void adj_list_graph_DFS_visit(const struct adj_list_graph *g);

/**< graphic implementation with adjacent matrics way */

/**< adj_matrix_graph: the adjacent matrix graph struct definition
 * @map: the matrix representation of the graph
 *
 * */
struct adj_matrix_graph
{
    int map[MAX_GNODES][MAX_GNODES];
};

void adj_matrix_graph_init(struct adj_matrix_graph **g);

boolean adj_matrix_graph_add_edge(struct adj_matrix_graph *g, const int start, const int end);
boolean adj_matrix_graph_dadd_edge(struct adj_matrix_graph *g, const int start, const int end);
boolean adj_matrix_graph_del_edge(struct adj_matrix_graph *g, const int start, const int end);
boolean adj_matrix_graph_ddel_edge(struct adj_matrix_graph *g, const int start, const int end);

void adj_matrix_graph_display(const struct adj_matrix_graph *g);
void adj_matrix_graph_BFS_visit(const struct adj_matrix_graph *g, const int vertex);
void adj_matrix_graph_DFS_recursive(const struct adj_matrix_graph *g, const int vertex);
void adj_matrix_graph_DFS_nonrecursive(const struct adj_matrix_graph *g, const int vertex);
void adj_matrix_graph_DFS_visit(const struct adj_matrix_graph *g);

#endif  /*GRAPH_H*/
