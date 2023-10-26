#include "readGraph.h"

void ExitError(char* miss, int errcode) { //error handling
  fprintf (stderr, "\nERROR: %s.\nStopping...\n\n", miss); exit(errcode);
}

#ifdef _WIN32
char* mystrsep(char** stringp, const char* delim) { //strsep function implementation for Windows. Taken from Stackoverflow
  char* start = *stringp; //original string is not modified
  char* p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;  //find the first occurrence of the delimeter

  if (p == NULL)  {
    *stringp = NULL;
  }
  else  {
    *p = '\0';
    *stringp = p + 1; //advance original string after the delimeter
  }

  return start;
}
#endif

int read(node** nodes, char *name){  //read the graph file
  FILE *fin;
  int nnodes;
  int i,j;
  char *buffer=NULL;
  size_t bufsize =0;
  size_t ch;
  char* delim=",";
  char* line2;
  
  //handle errors in the opening and reading
  if ((fin = fopen (name, "r")) == NULL)
    ExitError("the data file does not exist or cannot be opened", 11);
  
  if((ch=getline(&buffer,&bufsize,fin))==-1)
    ExitError("when reading header", 12);

  //create array of nodes
  nnodes=atoi(buffer);
  if(((*nodes) = (node*) malloc(nnodes*sizeof(node))) == NULL)
    ExitError("when allocating memory for the nodes vector", 13);
  
  //set the initial information of the nodes
  for(i=0; i<nnodes; i++){
    (*nodes)[i].id=i;
    (*nodes)[i].distance=infinity;
    (*nodes)[i].state=OPEN;
    (*nodes)[i].parent=-1;
    
    if((ch=getline(&buffer,&bufsize,fin))==-1)
      ExitError("when reading nsucc", 14);

    (*nodes)[i].nsucc=atoi(buffer); //number of adjacents nodes read

    if((*nodes)[i].nsucc>0){ //if there is at least an adjacent node
      //save memory for their id
      if(((*nodes)[i].succ=(int*)malloc((*nodes)[i].nsucc*sizeof(int)))==NULL)
          ExitError("allocating memory for successors", 15);
      
      if((ch=getline(&buffer,&bufsize,fin))==-1)
          ExitError("when reading successors", 16);

      //read and asign the id of the adjacent nodes. strsep function depends on OS
      line2=buffer;

      #ifdef _WIN32
      for(j=0; j<(*nodes)[i].nsucc; j++){
          (*nodes)[i].succ[j]=atoi(mystrsep(&line2,delim));
      }
      #endif 

      #ifdef linux
      for(j=0; j<(*nodes)[i].nsucc; j++){
          (*nodes)[i].succ[j]=atoi(strsep(&line2,delim));
      }
      #endif

      //save memory, read and asign the weigth of the edges
      if(((*nodes)[i].w=(float*)malloc((*nodes)[i].nsucc*sizeof(float)))==NULL)
          ExitError("allocating memory for weights", 15);
      
      if((ch=getline(&buffer,&bufsize,fin))==-1)
          ExitError("when reading weights", 16);
      
      line2=buffer;
      #ifdef _WIN32
      for(j=0; j<(*nodes)[i].nsucc; j++){
          (*nodes)[i].w[j]=logf(atof(mystrsep(&line2,delim)));
      }    
      #endif 

      #ifdef linux
      for(j=0; j<(*nodes)[i].nsucc; j++){
          (*nodes)[i].w[j]=logf(atof(strsep(&line2,delim)));
      }    
      #endif
    }
  }

  //close file and free memory
  fclose(fin); 
  free(buffer);
  buffer=NULL;

  return nnodes;
}

