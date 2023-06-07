#include<bits/stdc++.h>

using namespace std;


void nextval(string& p,int ne[]){
	int j=0,k=-1;
	ne[0]=-1;
	
	while(j<(int)p.size()-1){
		if(k==-1 || p[k]==p[j]){
			if(p[++k]==p[++j]) ne[j]=ne[k];
			else ne[j]=k;
		}else{
			k=ne[k];
		}
	}
}



bool kmp(string& s,string& p){//������ģʽ��
	int ne[10010]; 
	nextval(p,ne);//����nextval 
	
	int i=0,j=0;
	while(i<(int)s.size() &&j<(int)p.size()){
		if(j==-1 || s[i]==p[j]) i++,j++; 
		else j=ne[j];
	}
	
	if(j==(int)p.size()) return true;//ƥ��ɹ� 
	else return false; //ʧ�� 
}


//int main(){
//	string s="ddabcacabcad",p="abcac";
//	cout<<kmp(s,p);
//	return 0;
//} 
