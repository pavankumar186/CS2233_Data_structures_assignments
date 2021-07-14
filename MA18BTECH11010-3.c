/* 
Assignment 3
Roll Number: MA18BTECH11010 
Name: Pavan Kumar V.S Vemuri
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int comparision(char numberPlate0[],char numberPlate1[]){
  char s0[3],s1[3];
  s0[0]= numberPlate0[0];
  s0[1]= numberPlate0[1];
  s1[0]= numberPlate1[0];
  s1[1]= numberPlate1[1];
  if (s0[0]<s1[0] || (s0[0]==s1[0] && s0[1]<s1[1])){
    return 1;
  }
  else if (s0[0]==s1[0] && s0[1]==s1[1]){
    int num0=0,num1=0;
    for(int i=2;i<=5;i++){
      num0+=numberPlate0[i];
      num0*=10;
      num1+=numberPlate1[i];
      num1*=10;
    }
    if (num0<num1)
      return 1;
  }
      return 0;
}

int comparision2(char numberPlate0[],char numberPlate1[]){
  char s0[3],s1[3];
  s0[0]= numberPlate0[0];
  s0[1]= numberPlate0[1];
  s1[0]= numberPlate1[0];
  s1[1]= numberPlate1[1];
  if (s0[0]<s1[0] || (s0[0]==s1[0] && s0[1]<s1[1])){
    return 0;
  }
  else if (s0[0]==s1[0] && s0[1]==s1[1]){
    int num0=0,num1=0;
    for(int i=2;i<=5;i++){
      num0+=numberPlate0[i];
      num0*=10;
      num1+=numberPlate1[i];
      num1*=10;
    }
    if (num0==num1)
      return 1;
  }
      return 0;
}

struct bst {
  char np[7]; 
  struct bst *parent;
  struct bst *left;
  struct bst *right;
};

struct bst* create_node(char numberPlate[]){
  struct bst* temp=(struct bst*) malloc(sizeof(struct bst));
  temp->right=NULL;
  temp->left=NULL;
  temp->parent=NULL;
  int i=0;
  for(;i<7;i++){
    temp->np[i]=numberPlate[i];
  }
  return temp;
}

void insert(struct bst* temp,struct bst* node){
  int f=0;
  while(1){
    if (comparision(temp->np,node->np)){
      if (!node->left){
        f=1;
        break;
      }
      node=node->left;
    }
    else{
      if (!node->right){
        f=2;
        break;
      }
    node=node->right;
    }
  }
if(f==1){
  node->left=temp;
  temp->parent=node;
}
if(f==2){
  node->right=temp;
  temp->parent=node;
}
}

void inorder(struct bst *r){
   if (r==0)
    return;
    inorder(r->left);
    printf("%s ",r->np);
    inorder(r->right);
}

void postorder(struct bst *r){
   if (r==0)
    return;
    postorder(r->left);
    postorder(r->right);
    printf("%s ",r->np);
}

void freeing(struct bst *r){
   if (r==0)
    return;
    freeing(r->left);
    freeing(r->right);
    free(r);
    r=NULL; 
}

struct bst* search(struct bst* node,char numpla[]){
  if (comparision2(node->np,numpla)){
    return node;
  }
  while(!comparision2(node->np,numpla)){
    if(!comparision(node->np,numpla)){
      if (!node->left)
      break;
      node=node->left;
    }
    else{
      if (!node->right)
      break;
      node=node->right;
    }
  }
  if(comparision2(node->np,numpla)) {
    return(node);}
  else
    return(0);
}

void path(struct bst* node,char numpla[]){
  while(!comparision2(node->np,numpla)){
    if(!comparision(node->np,numpla)){
      if (!node->left)
      break;
      printf("L");
      node=node->left;
    }
    else{
      if (!node->right)
      break;
    printf("R");
      node=node->right;
    }
  }
}

char* successor(struct bst* node,char numpla[],struct bst* root){
  char* temp;
  while(!comparision2(node->np,numpla)){
    if(!comparision(node->np,numpla)){
      if (!node->left)
      break;
      node=node->left;
    }
    else{
      if (!node->right)
      break;
      node=node->right;
    }
  }
  if(comparision2(node->np,numpla)) {
    if(node->right!=NULL){
      node=node->right;
      while (node->left!=NULL)
        node=node->left;
      temp=node->np;
      return(temp);
    }
    else if(node->parent!=NULL) {
      while(node->parent!=NULL)
      {
        if (!comparision(node->parent->np,node->np))
        {
          temp=node->parent->np;
          return(temp);
        }
        node=node->parent;
      }
    }
  }
  else{
    if (comparision(numpla,node->np)){
      temp=node->np;
      return temp;
    }
    return successor(root,node->np,root);
  }
  return(NULL);
}

char* predecessor(struct bst* node,char numpla[],struct bst* root){
  char* temp;
  while(!comparision2(node->np,numpla)){
    if(!comparision(node->np,numpla)){
      if (!node->left)
      break;
      node=node->left;
    }
    else{
      if (!node->right)
      break;
      node=node->right;
    }
  }
  if(comparision2(node->np,numpla)) {
    if(node->left!=NULL){
      node=node->left;
      while (node->right!=NULL)
        node=node->right;
      temp=node->np;
      return(temp);
    }
    else if(node->parent!=NULL) {
      while(node->parent!=NULL)
      {
        if (comparision(node->parent->np,node->np))
        {
          temp=node->parent->np;
          return(temp);
        }
        node=node->parent;
      }
    }
  }
  else{
    if (!comparision(numpla,node->np)){
      temp=node->np;
      return temp;
    }
    return predecessor(root,node->np,root);
  }
  return(NULL);
}

int main(){
  char choice, numberPlate[7];
  _Bool requests = 0,first=1;
  struct bst* root;

  // Fetching till we hit the first request
   while(scanf("%s",numberPlate)!=-1){
    if(!requests){
      if(strlen(numberPlate) == 1){ // Detecting start of request lines.
	     choice = numberPlate[0];
	     requests = 1;
      }
      else{
        if(first){      
          root=create_node(numberPlate);
          first=0;
        }
        else{
          struct bst* temp=create_node(numberPlate);
          insert(temp,root);
        }	// *** Call your insert function here with argument numberPlate ***
      }
    }
    else break; // choice and numberPlate have values to be processed!!
   }
   do{ // Ugly do-while to process first request line before first scanf.
     if(choice == 'S'){
      struct bst* ans = search(root,numberPlate);
      if (ans==0)
        printf("0\n");
      else {
        printf("1 ");
        path(root,numberPlate);
        printf("\n");
      }
     }
     else if(choice == '<'){
      char *ans = predecessor(root,numberPlate,root);
      if (ans==NULL)
        printf("0\n");
      else
        printf("%s\n",ans);
       //*** Call your predecessor function here with argument numberPlate ***
     }
     else if(choice == '>'){
      char *ans = successor(root,numberPlate,root);
      if (ans==NULL)
        printf("0\n");
      else
        printf("%s\n",ans);
       //*** Call your successor function here with argument numberPlate ***
     }
     else if(choice == 'I'){
      inorder(root);
      printf("\n");
     }
     else if(choice == 'P'){
      postorder(root);
      printf("\n");
     }
     else if(choice == '-'){
      struct bst* ans = search(root,numberPlate);
      if (ans==0)
        printf("-1 \n");
      else{
        int child=0;
        if (ans->right!=NULL)
          child++;
        if (ans->left!=NULL)
          child++;
        printf("%d ",child);
        if(child==2){
          char *val = successor(root,numberPlate,root);
          printf("%s\n",val);
          struct bst* ans2 = search(root,val);
          int i=0;
          for(;i<7;i++){
            ans->np[i]=val[i];
            }
          ans=ans2;
          if (ans->right!=NULL){
          if (ans->parent->left==ans)
            ans->parent->left=ans->right;
          else 
            ans->parent->right=ans->right;
          ans->right->parent=ans->parent;
          
          }
          else if (ans->left!=NULL){
          if (ans->parent->left==ans)
            ans->parent->left=ans->left;
          else 
            ans->parent->right=ans->left;
          ans->left->parent=ans->parent;
          
          }
          else{
          if (ans->parent->left==ans)
            ans->parent->left=NULL;
          else 
            ans->parent->right=NULL;
          
        }
      }
        else if (child==1){
          if (ans->right!=NULL){
            printf("%s\n",ans->right->np);
            if (ans->parent==NULL){
              root=ans->right;
              ans->right->parent=NULL;
              }
            else{
            if (ans->parent->left==ans)
              ans->parent->left=ans->right;
            else 
              ans->parent->right=ans->right;
            ans->right->parent=ans->parent;
          }
          }
          if (ans->left!=NULL){
            printf("%s\n",ans->left->np);
          if (ans->parent==NULL){
              root=ans->left;
              ans->left->parent=NULL;
              }
          else{
          if (ans->parent->left==ans)
            ans->parent->left=ans->left;
          else 
            ans->parent->right=ans->left;
          ans->left->parent=ans->parent;
        }
          
          }
        }
        else{
          if (ans->parent==NULL){
              root=NULL;
              first=1;
              }
          else{
            if (ans->parent->left==ans)
              ans->parent->left=NULL;
            else
              ans->parent->right=NULL;
          }
          
          printf("\n");
        }
      free(ans);
      ans=NULL;
      }
    }
     else if(choice == '+'){
      if (first){
        root=create_node(numberPlate);
        first=0;
      }
      else{
      struct bst* ans = search(root,numberPlate);
      if (ans==0)
      {
        struct bst* temp=create_node(numberPlate);
        insert(temp,root);
      }
    }
     }
   }while(scanf("%*[\n]%c %6s",&choice, numberPlate)!=-1); 
   
   freeing((root));

   return(0);  
}