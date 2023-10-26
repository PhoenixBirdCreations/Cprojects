#include "readGraph.h"

struct List;

//Description of function arguments:
void readList(list *start); //pointer to start of the list
void cleanList(list *start); //pointer to start of the list
void push(list **start, node *put); //pointer to start of the list, node to insert
node* pop(list **start); //pointer to start of the list
void initialize(list **start, node* V, int N, int source); //pointer to start of the list, array of nodes, length of node array, source node index
int dijsktra(node *V, int N, int source,  int goal); //array of nodes, length of array of nodes, source node index, goal node index
void showPath(node *V, int goal, int source); //array of nodes, goal node index, source node index