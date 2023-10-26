#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define infinity -5000

enum state {OPEN,CLOSE};

typedef struct node{  //properties of directed graph node
  int id;  //identification label of the node
  float distance;    //distance travelled in the graph to reach the node
  int state;    //if all connections of the node have been explored
  int nsucc;    //number of nodes arising from this node (succesors)
  int *succ;    //array: id of nodes arising from this node
  float *w;     //array: weights of edges to adjacent nodes, same order as succ
  int parent;   //id of previous node in the constructed path
}node;

typedef struct List{  //linked list to handle nodes
  node *vertex; 
  struct List *next;
}list;