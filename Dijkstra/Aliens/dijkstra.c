#include "dijkstra.h"

void readList(list *start){ //traverse linked list reading consecutive nodes
  list *aux;
  aux=start;
  while(aux!=NULL){
    printf("Go to city %d, then...\n",(*(*aux).vertex).id);
    aux=(*aux).next;
  }
}

void cleanList(list *start){ //free the memory of the linked list
  list *aux,*aux2;
  aux=start;
  aux=aux->next;
  while(aux!=NULL) {
    aux2=aux->next; 
    aux->vertex=NULL;
    free(aux);
    aux=aux2;
  }
  start->vertex=NULL;
  free(start);
}

void push(list **start, node *put){ //add a node to the linked list
  list* aux;
  aux=(*start);
  (*start)=(list*)malloc(sizeof(list));
  (**start).vertex=put;
  (**start).next=aux;
}

node* pop(list **start){  //extract node with optimal cost in the linked list
  if((*start)==NULL){
    printf("Null queue to extract from\n"); exit(0); 
  }

  if((*start)->next==NULL){ // if there is no more nodes, extract the starting node
    node *thisNode;
    thisNode=(*start)->vertex;
    free(*start);
    (*start)=NULL;
    if (thisNode->distance==infinity) {
      printf("Extracted from queue node with infinite distance\n");
      return NULL;
    }
    return thisNode;
  }

  //If there is more than one node in the list, search the one with optimal cost
  float max=infinity;
  list* aux; //auxiliar list to explore the linked list
  list* father; //auxiliar list to control preceding node
  list* parent=NULL; //list with the information of the optimal node
  list* prev=NULL; //list with the information of the node previous to the optimal 

  aux=(*start);
  father=NULL;
  while(aux!=NULL){
    if(aux->vertex->distance>max){ //this particular problem requires maximizing the cost
      max=aux->vertex->distance;
      parent=aux;
      prev=father;
    }
    father=aux;
    aux=aux->next; 
  }

  //Optimal node located. Pop without losing the list.
  if(parent==NULL){ //to control that there was an optimal node
    printf("\n Node with infinite distance popped\n");
    return NULL;
  }

  node *thisNode;
  thisNode=parent->vertex; //the vertex to extract
  aux=parent->next; //reuse the variable, link to next node

  //the list structure was malloced before, it has to be free
  free(parent);
  parent=NULL;
 
  if(prev==NULL){ //if there is no previous node, the linked list now starts after the popped node
    (*start)=aux;
  }
  else{
    prev->next=aux;  //the linked list now skips the popped node
  }

  return thisNode;
}
 
void initialize(list **start, node* V, int N, int source){  //initialize the linked list
  int i;
  V[source].distance=0; //distance to origin node is zero
  
  (**start).vertex=V;
  (**start).next=NULL;

  for (i=1; i<N; i++)
    push(start, V+i);
}

int dijsktra(node* V, int N, int source, int goal){ //Dijsktra algorithm: find optimum path from source to goal
  list* start;
  start=(list*)malloc(sizeof(list));

  initialize(&start, V, N, source);

  node *u;
  int *aux;
  int i;
  float newDist;
  while(start!=NULL){
    u=pop(&start); //pop optimal node to continue
    if(u==NULL){ //if there is no way to continue, the node is isolated: clean and end in failure
      printf("Source node isolated from goal node\n");
        if(start!=NULL)
          cleanList(start);
      return -1;
    }

    if(u->id==goal){ //if the goald is reached, clean and end in success
      if(start!=NULL)
        cleanList(start);
      return u->id;
    }

    u->state=CLOSE; //declare the node explored
    aux=u->succ;
    for(i=0; i<u->nsucc; i++){ //explore adjacent nodes
      if(V[aux[i]].state==OPEN){
	      newDist=(u->distance)+(u->w)[i];
        if (V[aux[i]].distance<newDist){
          V[aux[i]].distance=newDist;
          V[aux[i]].parent=u->id;
        }
      }
    }    
  }

  //if the goal was not isolated and was not reached, some error ocurred. Clean and return failure
  printf("An error ocurred. Does destination exist?\n");
  if(start!=NULL) cleanList(start);
  return -2;
}

void showPath(node *V, int goal, int source){ //show the path found
  if (goal<0){ //If a route was not found
   printf("I want to believe that there is a route, but there's not. Sorry. \n");
   exit(0);
  }

  //If there is a route, show the cost and the path to follow
  printf("Detected Ln(prob of no-abduction): %.8f\n",V[goal].distance);
  printf("Probability of abduction on the road: %.2f %%\n",(1-expf(V[goal].distance))*100);
  printf("Path to drive without aliens:\n");
  int i;
  i=goal;
  list* start;
  start=(list*)malloc(sizeof(list));
  (*start).vertex=(V+i);
  (*start).next=NULL;
  while(i!=source){
    i=V[i].parent;
    push(&start,(V+i)); //create a list in reverse order to read appropriately
  }
  readList(start);
  printf("You have reached your destination\n");
  cleanList(start);
}

