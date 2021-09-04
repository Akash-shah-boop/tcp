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
   initialise_interface(node);
   dll_node_t* dll_node = create_node_with_data((void*)node);
   add_node_at_end(&graph->node_list, dll_node);
   return node;
}
/*
 * Name: insert_link_between_two_nodes
 * Function: this function creates a link between the two nodes and returns the pointer to the link
 * */
link_t* insert_link_between_two_nodes(node_t* node1, node_t* node2, int interfaceid1, int interfaceid2, int cost)
{
   //interfaceid should not be greater than MAX_INTERFACE_SIZE(10) - 1 i.e 9
   if(interfaceid1 > 9 || interfaceid2 > 9 || interfaceid1 < 0 || interfaceid2 < 0)
   return NULL;


   interface_t intf1[MAX_INTERFACE_SIZE], intf2[MAX_INTERFACE_SIZE];
   memcpy(intf1, node1->interf,sizeof(interface_t)*MAX_INTERFACE_SIZE);
   memcpy(intf2, node2->interf,sizeof(interface_t)*MAX_INTERFACE_SIZE);
   link_t* link = (link_t*)malloc(sizeof(link_t));
   link->interface1 = &intf1[interfaceid1];
   link->interface2 = &intf2[interfaceid2];
   link->cost = cost;
   intf1[interfaceid1].link = link;
   intf2[interfaceid2].link = link;
   memcpy(node1->interf,intf1,sizeof(interface_t)*MAX_INTERFACE_SIZE);
   memcpy(node2->interf,intf2,sizeof(interface_t)*MAX_INTERFACE_SIZE);
   return link;
}
  /*
 * Name: initialise_interface
 * Parameter : * node
 * Function: This function initialise the interface during node creation.
 *
 */

void initialise_interface(node_t* node)
{
   interface_t* interface_set = malloc(sizeof(interface_t)*MAX_INTERFACE_SIZE);
   for(int i = 0 ; i < MAX_INTERFACE_SIZE; i++)
      {

         char name[MAX_INTERFACE_NAME_SIZE];
	 snprintf(name,MAX_INTERFACE_NAME_SIZE,"eth%d",i);

         strncpy((interface_set + i)->interface_name, name, MAX_INTERFACE_NAME_SIZE);
         (interface_set+i)->node = node;
	 (interface_set+i)->link = NULL;


      }
   memcpy(node->interf, interface_set, sizeof(interface_set[0])*MAX_INTERFACE_SIZE);  
}

  /*
  * Name: get_node_interface_empty_slot
  * Func: it returns available slot id for a give node
  * 
  * */
int get_node_interface_empty_slot(node_t* node)
{
  interface_t intf[MAX_INTERFACE_SIZE];
  memcpy(intf, node->interf, sizeof(interface_t)*MAX_INTERFACE_SIZE);
  int i = 0;
  while(intf[i].link != NULL && i < 9)
  {
  i++;
  }
  if(i>9)
  return -1;
  else
  return i;
}
int main()
{

graph_t* graph = create_new_graph("Graph1");
node_t* node1 = create_new_node("node1", graph);
node_t* node2 = create_new_node("node2", graph);
//create_new_node("node3", graph);
link_t* link = insert_link_between_two_nodes(node1, node2,get_node_interface_empty_slot(node1),get_node_interface_empty_slot(node2),33);
dll_node_t* head = graph->node_list.head;
while(head != NULL)
{
node_t* node = (node_t*)head->data;
printf("%s ==>", node->node_name);
interface_t i[MAX_INTERFACE_SIZE];
memcpy(i, node->interf, sizeof(interface_t)*MAX_INTERFACE_SIZE);
for(int a = 0 ; a < MAX_INTERFACE_SIZE; a++)
{
printf("\n[%s %s %d]",i[a].interface_name, i[a].node->node_name, i[a].link?i[a].link->cost: -1);

}
head = head->right;
printf("\n");
}

//
printf("%d",get_node_interface_empty_slot(node1));
printf("%d",get_node_interface_empty_slot(node2));
return 0;
}

