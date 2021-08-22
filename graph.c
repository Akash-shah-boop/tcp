#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"

graph_t* create_new_graph(char* graph_name)
{
   graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
   strncpy(graph->graph_name, graph_name,32);
   graph->graph_name[32] = '\0';
   graph->node_list.head = NULL;
   graph->node_list.last = NULL;
   return graph;
}


node_t* create_new_node(char* node_name, graph_t* graph)
{
   //create a nod
   node_t* node = (node_t*)malloc(sizeof(node_t));
   strncpy(node->node_name, node_name, MAX_NODE_NAME_SIZE);
   node->node_name[MAX_NODE_NAME_SIZE - 1] = '\0';
   dll_node_t* dll_node = create_node_with_data((void*)node);
   add_node_at_end(&graph->node_list, dll_node); 
   return node;
}

void insert_link_between_two_nodes(node_t* node1, node_t* node2, interface_t* intf1, interface_t* intf2, int cost)
{
   

return;
}


int main()
{
graph_t* graph = create_new_graph("Graph1");
create_new_node("node1", graph);
create_new_node("node2", graph);
create_new_node("node3", graph);
dll_node_t* head = graph->node_list.head;
while(head != NULL)
{
node_t* node = (node_t*)head->data;
printf("%s", node->node_name);
head = head->right;
}


return 0;
}

