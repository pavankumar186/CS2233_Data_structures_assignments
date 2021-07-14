#include<iostream>
#include <string.h> 

using namespace std;
void comparision(string numberPlate0,string numberPlate1){
	int f=0;
	string s0 = numberPlate0.substr(0, 2);
	string s1 = numberPlate1.substr(0, 2);
	if (s0[0]<s1[0] || (s0[0]==s1[0] && s0[1]<s1[1])){
		cout<< 1<<"\n"; 
		f=1;
	}
	else if (s0[0]==s1[0] && s0[1]==s1[1]){
		s0 = numberPlate0.substr(2, 6);
		s1 = numberPlate1.substr(2,6);
		for(int i=0;i<=3;i++){
			if (s0[i]<s1[i]){
				cout<< 1<<"\n"; 
				f=1;
				break;
			}
			else if(s0[i]>s1[i]){
				break;
			}
		}
	}
	if (f==0)
		cout<< 0 <<"\n";
}

int main(){
  string numberPlate[2];
  bool act=0;
  while (cin >> numberPlate[act]){
	act=1-act;
	if(act==0)
		comparision(numberPlate[0],numberPlate[1]);
}
return(0);
}