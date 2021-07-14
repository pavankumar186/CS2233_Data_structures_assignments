/* 
Assignment 5
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

struct wnode
{
  struct wnode* address;
  int val;
  int w;
};

int numberOfVertices,copy;

struct wnode* CreateNode(int v2,int w){
  struct wnode* p1 = (struct wnode*) malloc(sizeof(struct wnode));
  p1->val=v2;
  p1->w=w;
  p1->address=NULL;
  return p1;
}
void CreateEdge(struct wnode* p,int v1,int v2,int w){
  struct wnode* poi=&p[v1];
  while(poi->address!=NULL){
    poi=poi->address;
  }
  poi->address=CreateNode(v2,w);
}

void markstart(struct wnode* pq,int v1){
  struct wnode temp;
  pq[v1].w=0;
  temp=pq[0];
  pq[0]=pq[v1];
  pq[v1]=temp;
}

void refresh(struct wnode* pq,struct wnode* p, int* parent){
  int i;
  for (i = 0; i < numberOfVertices; ++i)
  {
    pq[i].val=i;
    pq[i].w=-1;
    pq[i].address=&p[i];
    parent[i]=-1;
  }
}

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

int check(struct wnode* pq,int v1,int v2){
  if ((pq[v2].w!=-1 && pq[v1].w!=-1 && (pq[v1].w<pq[v2].w || (pq[v1].w==pq[v2].w && pq[v1].val<pq[v2].val)) )||(pq[v2].w==-1 && pq[v1].w!=-1)||(pq[v2].w==-1 && pq[v1].w==-1 && pq[v1].val<pq[v2].val))
    return v1;
  else
    return v2;
}

void correctheap(struct wnode* pq, int v){
  if (2*v+1>=numberOfVertices)
    return;
  struct wnode temp;
  int min;
  min=check(pq,v,2*v+1);
  if (min==2*v+1){
    if (2*v+2==numberOfVertices)
    {
      temp=pq[2*v+1];
      pq[2*v+1]=pq[v];
      pq[v]=temp;
      return;
    }
    min=check(pq,2*v+1,2*v+2);
    if (min==2*v+1){
      temp=pq[2*v+1];
      pq[2*v+1]=pq[v];
      pq[v]=temp;
      correctheap(pq,2*v+1);
    }
    else{
      temp=pq[2*v+2];
      pq[2*v+2]=pq[v];
      pq[v]=temp;
      correctheap(pq,2*v+2); 
    }
  }
  else{
    if (2*v+2==numberOfVertices)
      return;
    min=check(pq,v,2*v+2);
    if (min==2*v+2){
      temp=pq[2*v+2];
      pq[2*v+2]=pq[v];
      pq[v]=temp;
      correctheap(pq,2*v+2);   
    }
  }
}

void heapify(struct wnode* pq, int v){
  int min;
  struct wnode temp;
  if(v%2==1){
    if(v+1==numberOfVertices)
      min=v;
    else
      min=check(pq,v,v+1);
    if (min==v){
      min=check(pq,v,v/2);
    }
    if (min==v){
      temp=pq[v/2];
      pq[v/2]=pq[v];
      pq[v]=temp;
      heapify(pq,v/2);
    }
  }
  else if(v>1){
    min=check(pq,v,v-1);
    if (min==v){
      min=check(pq,v,(v/2)-1);
    }
    if (min==v){
      temp=pq[(v/2)-1];
      pq[(v/2) - 1]=pq[v];
      pq[v]=temp;
      heapify(pq,(v/2)-1);
    }
  }
}

struct wnode extractmin(struct wnode* pq){
  struct wnode temp;
  struct wnode min=pq[0];
  if(pq[0].w!=-1 && didntVisit(pq[0].val)){
    temp=pq[0];
    pq[0]=pq[numberOfVertices-1];
    pq[numberOfVertices-1]=temp;
    numberOfVertices--;
    if (numberOfVertices>0)
      correctheap(pq,0);
    visited(min.val);
  }
  else
    min.address=NULL;
  return min;
}

struct wnode* search(struct wnode* pq, int v){
  int i;
  for (i = 0; i < numberOfVertices; ++i)
  {
    if (pq[i].val==v)
      break;
  }
  return &pq[i];
}

int indexnum(struct wnode* pq, int v){
  int i;
  for (i = 0; i < numberOfVertices; ++i)
  {
    if (pq[i].val==v)
      break;
  }
  return i;
}


void update(struct wnode* pq,struct wnode* ver, int cur, int* parent){
  struct wnode* temp=ver;
  struct wnode* temp2;
  temp=temp->address;
  while(temp!=NULL){ 
    if (didntVisit(temp->val)){ 
      temp2=search(pq,temp->val);
      if ((temp->w + cur)<(temp2->w) || (temp2->w)==-1){        
        (temp2->w)=(temp->w + cur);
        parent[temp->val]=ver->val;
        heapify(pq,indexnum(pq,temp->val));
      }
    }
      temp=temp->address;
  }
}

void path(int v1,int v2, int* parent){
  int final[copy+1];
  int temp,i=1;
  final[0]=v2;
  while(temp!=v1){
    temp=parent[final[i-1]];
    final[i]=temp;
    i++;    
  }
  i--;
  while(i>-1){
    printf("%d ",final[i]);
    i--;
  }
  printf("\n");
}

void Dij(struct wnode* p,struct wnode* pq,int v1,int v2, int* parent){
  if(v1==v2){
    printf("0 %d\n",v1);
    return;
  }
  markstart(pq,v1);
  int currLen;
  struct wnode ver, *u;
  while(ver.val!=v2){
    ver=extractmin(pq);
    if(ver.address==NULL)
      break;
    currLen=ver.w;
    update(pq,ver.address,currLen,parent);
  }
  u=search(pq,v2);
  if(u->w!=-1){
    printf("%d ",u->w);
    path(v1,v2,parent);
  }
  else
    printf("-1\n");
  numberOfVertices=copy;
  cleanVisit();
  refresh(pq,p,parent);
}

int main(){
  char choice;
  int startVertex, endVertex,i,weight;
  // Fetching number of vertices
  scanf("%d",&numberOfVertices);
  copy=numberOfVertices;
  // Create your adjacency list's array of head vertices here.
  struct wnode *p= (struct wnode*) malloc(sizeof(struct wnode)*numberOfVertices);
  struct wnode *pq= (struct wnode*) malloc(sizeof(struct wnode)*numberOfVertices);  
  int *parent=(int*) malloc(sizeof(int)*numberOfVertices+1);
  for (i = 0; i < numberOfVertices; ++i)
  {
    p[i].val=i;
    p[i].w=i;
    p[i].address=NULL;
    pq[i].val=i;
    pq[i].w=-1;
    pq[i].address=&p[i];
    parent[i]=-1;
  } 
  // printf("entering loop\n");
  while(scanf(" %c",&choice)!=-1){
     if(choice == 'N'){
       char delimiter;
       scanf("%d", &startVertex);
       // printf("entering 2nd loop\n"); 
       while(scanf("%d %d%c", &endVertex,&weight, &delimiter)){
          if(startVertex!=endVertex)
          CreateEdge(p,startVertex,endVertex,weight);
	     // Add the edge (startVertex, endVertex) to your graph here.
	        if(delimiter == '\n') break; // Detecting end of line.
       }
     }
     else if(choice == 'D'){
       scanf("%d %d",&startVertex,&endVertex);
       Dij(p,pq,startVertex,endVertex,parent);
     }
   }
   struct wnode *start,*temp;
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
   free(pq);
   free(parent);
   return(0);  
}
