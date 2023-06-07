#include<bits/stdc++.h>
#include<conio.h>
#include "GUI.h"
#include "func.h"

using namespace std;

int GUIinit(char* name,char* uid){
	char op='0';
	system("cls"); 
	cout<<"*****************************************\n";
	cout<<"*\t     借还图书记录管理系统   \t*\n";
	cout<<"*\t\t欢迎你,"<<name<<"\t\t*\n";
	cout<<"*****************************************\n";
	cout<<"*\t\t请选择功能列表\t\t*\n";
	cout<<"*****************************************\n";
	cout<<"*\t\t1.借入图书\t\t*\n";
	cout<<"*\t\t2.归还图书\t\t*\n";
	cout<<"*\t\t3.打印借书信息\t\t*\n";
	cout<<"*\t\t4.保存借书信息\t\t*\n";
	cout<<"*\t\t5.追加借书信息\t\t*\n";
	cout<<"*\t\t6.统计借书信息\t\t*\n";
	cout<<"*\t\t7.查找借书信息\t\t*\n";
	cout<<"*\t\t8.修改借书信息\t\t*\n";
	cout<<"*\t\t0.退出系统\t\t*\n";
	cout<<"*****************************************\n";
	op=getch(); 
	switch(op-'0'){
		case 1:inputInfo(uid);break;
		case 2:removeInfo(uid);break;
		case 3:printInfo(uid,name);break;
		case 4:saveInfo(uid);break;
		case 5:readInfo(uid,1);break;
		case 6:cntInfo(uid,name);break;
		case 7:findInfo(uid,name);break;
		case 8:modifyInfo(uid);break;
		default:if(quit()){
			return 0;
		}else{
			return 1;
		}
	}
	return 1;
} 

bool login(){
	char userNum[11],pwd[20];
	char uid[11],up[20],name[10];
	system("cls");
	cout<<"*****************************************\n";
	cout<<"*\t  记录管理系统注册界面\t\t*\n";
	cout<<"*****************************************\n";
	cout<<"请输入学号：";
	cin>>userNum;
	cout<<"请输入密码：";
	char in;
	for(int i=0;in=getch();i++){
		if(in=='\n'||in=='\r'){
			pwd[i]='\0';
			cout<<'\n';
			break;
		}else if(in=='\b'){
			if(i>0){
				i-=2;
				cout<<"\b \b";
				pwd[i+1]='\0';
			}else{
				i=-1;
				continue;
			}
		}else{
			pwd[i]=in;
			cout<<'*';	
		}
	}
	
	 
	ifstream tifile("./USER",ios::binary);
	if(!tifile.is_open()){
		tifile.close();
		cout<<"账户不存在，是否创建新账户？(Y/n)：";
		char op=getch();
		if(op=='Y') signUp();
	}
	
	ifstream ifile("./USER",ios::binary);
	bool matchFlag=0;
	while(!ifile.eof()){
		ifile>>uid>>up>>name;
		if(!strcmp(uid,userNum)){//match
			matchFlag=1;
			if(!strcmp(up,pwd)){
				while(GUIinit(name,uid));
				return 0;//程序结束 
			} 
		}
	}
	ifile.close();
	
	
	if(matchFlag){
		cout<<"RE：密码错误"; 
	}else{
		cout<<"账户不存在，是否创建新账户？(Y/n)：";
		char op=getch();
		if(op=='Y') signUp();
	}
	
	return 1;//程序继续 
}

void signUp(){
	system("cls");
	cout<<"*****************************************\n";
	cout<<"*\t  记录管理系统注册界面\t\t*\n";
	cout<<"*****************************************\n";
	char userNum[11],pwd[20],name[10];
	cout<<"请输入学号：";
	cin>>userNum;
	cout<<"请输入密码：";
	cin>>pwd;
	cout<<"请输入姓名：";
	cin>>name;
	ofstream ofile("./USER",ios::binary);
	ofile<<userNum<<" "<<pwd<<" "<<name<<endl;
	ofile.close(); 
	cout<<"SEC：用户"<<name<<"已注册成功\n";
	cout<<"<<按任意键以退出注册界面>>";
	system("pause>nul"); 
	return;
}

//int main(){
//	GUIinit("严森","2208010132");
//}
