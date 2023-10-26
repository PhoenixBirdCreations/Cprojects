#include "dijkstra.h"

int main(int argc, char *argv[]){
  char name[50];
  int origin;
  int dest;

  if (argc !=4 
      || sscanf(argv[1],"%s",name)!=1
      || sscanf(argv[2],"%d",&origin)!=1
      || sscanf(argv[3],"%d",&dest)!=1
  ){
    fprintf(stderr, "./alien_route filename, origin node id, destination node id\n");
    return -1;
  }

  node *nodes;
  int nnodes;
  int reached;
  nnodes=read(&nodes,name); //read the graph
  reached=dijsktra(nodes, nnodes, origin, dest); //find the path between source and destination
  showPath(nodes, reached, origin); // print solution

  for (int i=0; i<nnodes; i++){ //clean memory
    if(nodes[i].nsucc>0){ 
      free(nodes[i].succ); 
      free(nodes[i].w); 
      nodes[i].succ=NULL;
      nodes[i].w=NULL;
    }
  }
  
  free(nodes);
  return 0;
}