#include  "graph.h"

//all the nodes of the graph are NOT visited originally
static int visited[MAX_GNODES];

/**< vertex_node_new: create a new vertex node
 * @key: the value of the node to be created
 *
 * */
struct vertex_node *vertex_node_new(const int key)
{
    struct vertex_node *new = malloc(sizeof(struct vertex_node));
    assert(new);
    new->key = key;
    new->next = NULL;
    return new;
}

/**< adj_list_graph_init: initiate the graph
 * @g: the graph to be initialized
 *
 * */
void adj_list_graph_init(struct adj_list_graph **g)
{
    *g = malloc(sizeof(struct adj_list_graph));
    assert(*g);
    int i;
    for( i=0 ; i<MAX_GNODES ; i++ )
    {
        (*g)->vertics[i].key = i;
        (*g)->vertics[i].next = NULL;
    }
}

/**< adj_list_graph_add_edge: add an single edge to the graph
 * @g: the graph the single edge to be added into
 * @start: the start node of the edge
 * @end: the end node of the edge
 *
 * description: if the edge already exist, the edge will not add to the graph
 * and print an information to remind.
 * */
boolean adj_list_graph_add_edge(struct adj_list_graph *g, const int start, const int end)
{
    assert(g);
    struct vertex_node *p = g->vertics[start].next;
    while( p )
    {
        if( p->key == end )
        {
            printf("the edge %d->%d is already in the graph!\n", start, end);
            return false;
        }
        p = p->next;
    }
    struct vertex_node *new = vertex_node_new(end);
    //add new node into the first place of the adjacent list
    new->next = g->vertics[start].next;
    g->vertics[start].next = new;
    return true;
}

/**< adj_list_graph_dadd_edge: add an double edge to the graph
 * @g: the graph the double edge to be added into
 * @start: the start node of the edge
 * @end: the end node of the edge
 *
 * description: if either the edge, which means from @start to @end or from
 * @end to @start are not exist, the edge will be added into the graph.
 * However, if both of them are exist alreay, none of them will be added.
 * Related information will be popped up also.
 * */
boolean adj_list_graph_dadd_edge(struct adj_list_graph *g, const int start, const int end)
{
    assert(g);
    //comment it up, if the first part is true then the second part will NOT
    //execute
    //return adj_list_graph_add_edge(g,start,end) || adj_list_graph_add_edge(g,end,start);
    boolean a = adj_list_graph_add_edge(g,start,end);
    boolean b = adj_list_graph_add_edge(g,end,start);
    return a&&b;
}

/**< adj_list_graph_del_edge: del an single edge from the graph
 * @g: the graph the single edge to be deleted from
 * @start: the start node of the edge
 * @end: the end node of the edge
 *
 * description: if the edge to be deleted does not exist, related information
 * will be popped up.
 *
 * */
boolean adj_list_graph_del_edge(struct adj_list_graph *g, const int start, const int end)
{
    assert(g);
    struct vertex_node *p = &g->vertics[start];
    while( p->next )
    {
        if( p->key == end )
        {
            struct vertex_node *del = p->next;
            p->next = del->next;
            free(del);
            return true;
        }
        p = p->next;
    }
    printf("the edge %d->%d does not exist!\n",start, end);
    return false;
}

/**< adj_list_graph_ddel_edge: del an double edge from the graph
 * @g: the graph the double edge to be deleted from
 * @start: the start node of the edge
 * @end: the end node of the edge
 *
 * description: if either the edge, which means from @start to @end or from
 * @end to @start are exist, the edge will be deleted from the graph.
 * However, if none of them are exist yet, none of them will be deleted.
 * Related information will be popped up also.
 *
 * */
boolean adj_list_graph_ddel_edge(struct adj_list_graph *g, const int start, const int end)
{
    assert(g);
    //comment it up, if the first part is true then the second part will NOT
    //execute
    //return adj_list_graph_del_edge(g,start,end) || adj_list_graph_del_edge(g,end,start);
    boolean a = adj_list_graph_del_edge(g,start,end);
    boolean b = adj_list_graph_del_edge(g,end,start);
    return a&&b;
}

/**< adj_list_graph_display: display the adjacent list graph
 * @: the graph to be displayed
 *
 * */
void adj_list_graph_display(const struct adj_list_graph *g)
{
    int i;
    for( i=0 ; i<MAX_GNODES ; i++ )
    {
        printf("V%d", g->vertics[i].key);
        struct vertex_node *t = g->vertics[i].next;
        while( t )
        {
            printf("%5d",t->key);
            t = t->next;
        }
        puts("");
    }
}

/**< adj_list_graph_BFS: adjacent list graph breadth first searching
 * @g: the graph to be searched
 * @vnode: the node to be searched begin with
 *
 * */
void adj_list_graph_BFS_visit(const struct adj_list_graph *g, const struct vertex_node *vnode)
{
    assert(g);
    assert(vnode);
    struct generic_queue *qu = NULL;
    generic_queue_init(&qu,sizeof(struct vertex_node *));
    generic_queue_in(qu,&vnode);
    while( !generic_queue_isempty(qu) )
    {
        const struct vertex_node *entry = NULL;
        generic_queue_out(qu,&entry);
        if( !visited[entry->key] )
        {
            printf("V%-5d",entry->key);
            visited[entry->key] = 1;
            struct vertex_node *t = g->vertics[entry->key].next;
            while( t )
            {
                generic_queue_in(qu,&t);
                t = t->next;
            }
        }
    }
}

/**< adj_list_graph_DFS_recursive: adjacent list graph depth first searching
 * @g: the graph to be searched
 * @vnode: the node to be searched begin with
 *
 * */
void adj_list_graph_DFS_recursive(const struct adj_list_graph *g, const struct vertex_node *vnode)
{
    if( !visited[vnode->key] )
    {
        printf("V%-5d",vnode->key);
        visited[vnode->key] = 1;
        const struct vertex_node *t = g->vertics[vnode->key].next;
        while( t )
        {
            if( !visited[t->key] )
            {
                adj_list_graph_DFS_recursive(g,t);
            }
            t = t->next;
        }
    }
}

/**< adj_list_graph_DFS_nonrecursive: adjacent list graph depth first searching
 * with non-recursive way.
 * @g: the graph to be searched
 * @vnode: the node to be searched begin with
 *
 * */
void adj_list_graph_DFS_nonrecursive(const struct adj_list_graph *g, const struct vertex_node *vnode)
{
    struct generic_stack *st = NULL;
    generic_stack_init(&st,sizeof(struct vertex_node *));
    generic_stack_push(st,&vnode);
    while( !generic_stack_isempty(st) )
    {
        const struct vertex_node *entry = NULL;
        generic_stack_pop(st,&entry);
        if( !visited[entry->key] )
        {
            printf("V%-5d",entry->key);
            visited[entry->key] = 1;
            const struct vertex_node *t = g->vertics[entry->key].next;
            while( t )
            {
                generic_stack_push(st,&t);
                t = t->next;
            }
        }
    }
}

/**< adj_list_graph_DFS_recursive: adjacent list graph depth first searching
 * @g: the graph to be searched
 *
 * */
void adj_list_graph_DFS_visit(const struct adj_list_graph *g)
{
    assert(g);
    int i;
    for( i=0 ; i<MAX_GNODES ; i++ )
    {
        //adj_list_graph_DFS_recursive(g,&g->vertics[i]);
        adj_list_graph_DFS_nonrecursive(g,&g->vertics[i]);
    }
}
