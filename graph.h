
#ifndef __GRAPH__
#define __GRAPH__


#include "../../development_libraries/development_lib/dll.h"
#define MAX_NODE_NAME_SIZE 32
#define MAX_INTERFACE_SIZE 10
#define MAX_INTERFACE_NAME_SIZE 32
typedef struct node_ node_t;
typedef struct interface_ interface_t;
typedef struct graph_ graph_t;
typedef struct link_ link_t;
typedef struct graph_
{
    char graph_name[32];
    dll_t node_list;

}graph_t;

typedef struct link_
{
    interface_t* interface1;
    interface_t* interface2;
    int cost;
}link_t;

typedef struct node_
{
    char node_name[MAX_NODE_NAME_SIZE];
    interface_t* interf[MAX_INTERFACE_SIZE];
     
}node_t;


typedef struct interface_
{
    char interface_name[MAX_INTERFACE_NAME_SIZE];
    node_t* node;
    link_t* link;
}interface_t;

graph_t* create_new_graph(char* graph_name);

node_t* create_new_node(char* node_name, graph_t* graph);

link_t* insert_link_between_two_nodes(node_t* node1, node_t* node2, int intf1, int intf2, int cost);

void initialise_interface(node_t* node);
#endif  // __GRAPH__
