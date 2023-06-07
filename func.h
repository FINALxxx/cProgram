#include<bits/stdc++.h>
using namespace std;

struct node{
	//图书名称，isdn，出版社，图书类别，所在区域，作者 
	string actName,aid,actHold,actCat,actLimit,actAdmin; 
	node* nxt;
	node(string actName,
		string aid,
		string actHold,
		string actCat,
		string actLimit,
		string actAdmin,
		node* nxt):actName(actName),aid(aid),actHold(actHold),actCat(actCat),actLimit(actLimit),actAdmin(actAdmin),nxt(nxt){}
};

void inputInfo(char* uid);
void printInfo(char* uid,char* name);
void saveInfo(char* uid);
bool readInfo(char* uid,bool flag);
void cntInfo(char* uid,char* name);
void findInfo(char* uid,char* name);
void modifyInfo(char* uid);
void removeInfo(char* uid);
bool quit();

