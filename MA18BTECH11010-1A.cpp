#include<iostream>
#include<sstream>
#include<iterator>
#include <cstring>
#include <string>


using namespace std;
int comparision(string numberPlate0,string numberPlate1){
  // int f=0;
  string s0 = numberPlate0.substr(0, 2);
  string s1 = numberPlate1.substr(0, 2);
  if (s0[0]<s1[0] || (s0[0]==s1[0] && s0[1]<s1[1])){
    return 1;
  }
  else if (s0[0]==s1[0] && s0[1]==s1[1]){
    s0 = numberPlate0.substr(2, 6);
    s1 = numberPlate1.substr(2,6);
    for(int i=0;i<=3;i++){
      if (s0[i]<s1[i]){
        return 1; 
      }
      else if(s0[i]>s1[i]){
        return 0;
      }
    }
  }
  return 0;
}

class bst{
public: 
  string np; 
  bst *parent,*left, *right;

  bst(string n){
    this->np=n;
    this->parent=NULL;
    this->left=NULL;
    this->right=NULL;
  }
};

void insert(string numberPlate,bst* node){
  bst* temp=new bst(numberPlate);
  int f=0;
  while(1){
    if (comparision(numberPlate,node->np)){
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
string search(bst* node,string numpla){
  string temp="";
  while(node->np!=numpla){
    if(!comparision(node->np,numpla)){
      temp=temp+"L";
      if (!node->left)
      break;
      node=node->left;
    }
    else{
      temp=temp+"R";
      if (!node->right)
      break;
      node=node->right;
    }

  }
  if(node->np==numpla) 
    return(temp);
  else
    return("n");
}

int main(){
  string firstLine;
  string numberPlate;
  char choice;
  //Fetching only the first line of input.
  getline(cin,firstLine);
  stringstream stringSplitter(firstLine);
  // Parsing the string word by word.
  
  bst* ru=new bst("1");
  while(stringSplitter >> numberPlate){
    if (ru->np=="1"){
    //since we know the numberplate always starts with an alphabet
      ru->np=numberPlate;
    }
    // Call your BST Insert function here with argument: numberPlate
    else
      insert(numberPlate,ru);
  }
  // Inorder(ru);
  // Main input handler to serve requests.
  // cout<<"insert done";
  while(cin >> choice >> numberPlate){
    if(choice=='S'){
      // Call your BST Search function here with argument: numberPlate
      string ans;
      ans = search(ru,numberPlate);
      if (ans=="n")
        cout<<0<<endl;
      else
        cout<<1<<" "<<ans<<endl;
    }
  }
  
  return(0);
}
 
  