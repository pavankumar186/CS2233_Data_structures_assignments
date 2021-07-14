/* 
Assignment 4
Roll Number: MA18BTECH11010
Name: Pavan Kumar V.S Vemuri
*/
#include<stdio.h>
#include <stdlib.h>
struct node
{
  struct node* address;
  int val;
};

int numberOfVertices;

struct node* head=NULL;
struct node* tail=NULL;
struct node* visitHead=NULL;
struct node* visitTail=NULL;

void cleanVisit(){
  struct node* temp;
  while(visitHead!=NULL){
  temp=visitHead;
  visitHead=visitHead->address;
  free(temp);
  }
  visitTail=NULL;
}


void visited(int v){
  if (visitHead==NULL){
    visitHead=(struct node*) malloc(sizeof(struct node));
    visitHead->address=NULL;
    visitHead->val=v;
    visitTail=visitHead;
  }
  else{
    visitTail->address=(struct node*) malloc(sizeof(struct node));
    visitTail=visitTail->address;
    visitTail->val=v;
    visitTail->address=NULL;
  }
}

int didntVisit(int v){
  struct node* poi=visitHead;
  while(poi!=NULL){
    if(poi->val==v)
      return 0;
    poi=poi->address;
  }
 return 1;
}

void enqueue(int v){
  if(head==NULL && tail==NULL){
    if (didntVisit(v)){
      head=(struct node*) malloc(sizeof(struct node));
      tail=head;
      tail->val=v;
      tail->address=NULL;
      visited(v);

    }
  }
  else{
    if (didntVisit(v)){
      tail->address=(struct node*) malloc(sizeof(struct node));
      tail=tail->address;
      tail->val=v;
      tail->address=NULL;
      visited(v);
    }
  }
}

int deque(){
  struct node* temp=head;
  if(head->address!=NULL){
    head=head->address;
  }
  else{
    head=NULL;
    tail=NULL;
  }
  int val=temp->val;
  free(temp);
  return val;
}

void sortedEnqueue(struct node *pa){
  int array[numberOfVertices];
  int i=0;
  pa=pa->address;
  while(pa!=NULL){
    array[i]=pa->val;
    i++;
    pa=pa->address;
  }
  int n=i;
  int min,j,temp,index;
  for(i=0;i<n;i++){
    min=array[i];
    index=i;
    for(j=i;j<n;j++){
      if(array[j]<min){
        min=array[j];
        index=j;
      }
    }
    if(didntVisit(min)){
      enqueue(min);
    }
    temp=array[i];
    array[i]=min;
    array[index]=temp;
  }

}

void BFS(struct node* p,int vertex){
  struct node *pa;
  enqueue(vertex);
  // printf("1st done\n");
  while(head!=NULL){
    // printf("%d\n",head);
    vertex=deque();
    // printf("%d########\n",head );
    printf("%d ",vertex );
    pa=&p[vertex];
    sortedEnqueue(pa);
  }
  cleanVisit();
  printf("\n");
}

struct node* CreateNode(int v2){
  struct node* p1 = (struct node*) malloc(sizeof(struct node));
  p1->val=v2;
  p1->address=NULL;
  return p1;
}
void CreateEdge(struct node* p,int v1,int v2){
  struct node* poi=&p[v1];
  while(poi->address!=NULL){
    poi=poi->address;
  }
  poi->address=CreateNode(v2);
  poi=&p[v2];
  while(poi->address!=NULL){
    poi=poi->address;
  }
  poi->address=CreateNode(v1);
}


int main(){
  char choice;
  int startVertex, endVertex,i;
  // Fetching number of vertices
  scanf("%d",&numberOfVertices);
  // Create your adjacency list's array of head vertices here.
  struct node *p= (struct node*) malloc(sizeof(struct node)*numberOfVertices);
  for (i = 0; i < numberOfVertices; ++i)
  {
    p[i].val=i;
    p[i].address=NULL;
  }
  // printf("entering loop\n");
  while(scanf(" %c",&choice)!=-1){
     if(choice == 'N'){
       char delimiter;
       scanf("%d", &startVertex);
       // printf("entering 2nd loop\n"); 
       while(scanf("%d%c", &endVertex, &delimiter)){
          if(startVertex!=endVertex)
          CreateEdge(p,startVertex,endVertex);
	     // Add the edge (startVertex, endVertex) to your graph here.
	        if(delimiter == '\n') break; // Detecting end of line.
       }
     }
     else if(choice == 'B'){
       scanf("%d",&startVertex);
       BFS(p,startVertex);
       // Call BFS on your graph starting from startVertex here.
     }
   }
   struct node *start,*temp;
   for ( i = 0; i < numberOfVertices; ++i)
   {  
    start=(p[i]).address;
    while(start!=NULL){
      temp=start;
      start=start->address;
      free(temp);
    }
   }
   free(p);
   return(0);  
}
