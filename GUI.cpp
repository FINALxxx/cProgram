#include<bits/stdc++.h>
#include<conio.h>
#include "GUI.h"
#include "func.h"

using namespace std;

int GUIinit(char* name,char* uid){
	char op='0';
	system("cls"); 
	cout<<"*****************************************\n";
	cout<<"*\t     �軹ͼ���¼����ϵͳ   \t*\n";
	cout<<"*\t\t��ӭ��,"<<name<<"\t\t*\n";
	cout<<"*****************************************\n";
	cout<<"*\t\t��ѡ�����б�\t\t*\n";
	cout<<"*****************************************\n";
	cout<<"*\t\t1.����ͼ��\t\t*\n";
	cout<<"*\t\t2.�黹ͼ��\t\t*\n";
	cout<<"*\t\t3.��ӡ������Ϣ\t\t*\n";
	cout<<"*\t\t4.���������Ϣ\t\t*\n";
	cout<<"*\t\t5.׷�ӽ�����Ϣ\t\t*\n";
	cout<<"*\t\t6.ͳ�ƽ�����Ϣ\t\t*\n";
	cout<<"*\t\t7.���ҽ�����Ϣ\t\t*\n";
	cout<<"*\t\t8.�޸Ľ�����Ϣ\t\t*\n";
	cout<<"*\t\t0.�˳�ϵͳ\t\t*\n";
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
	cout<<"*\t  ��¼����ϵͳע�����\t\t*\n";
	cout<<"*****************************************\n";
	cout<<"������ѧ�ţ�";
	cin>>userNum;
	cout<<"���������룺";
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
		cout<<"�˻������ڣ��Ƿ񴴽����˻���(Y/n)��";
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
				return 0;//������� 
			} 
		}
	}
	ifile.close();
	
	
	if(matchFlag){
		cout<<"RE���������"; 
	}else{
		cout<<"�˻������ڣ��Ƿ񴴽����˻���(Y/n)��";
		char op=getch();
		if(op=='Y') signUp();
	}
	
	return 1;//������� 
}

void signUp(){
	system("cls");
	cout<<"*****************************************\n";
	cout<<"*\t  ��¼����ϵͳע�����\t\t*\n";
	cout<<"*****************************************\n";
	char userNum[11],pwd[20],name[10];
	cout<<"������ѧ�ţ�";
	cin>>userNum;
	cout<<"���������룺";
	cin>>pwd;
	cout<<"������������";
	cin>>name;
	ofstream ofile("./USER",ios::binary);
	ofile<<userNum<<" "<<pwd<<" "<<name<<endl;
	ofile.close(); 
	cout<<"SEC���û�"<<name<<"��ע��ɹ�\n";
	cout<<"<<����������˳�ע�����>>";
	system("pause>nul"); 
	return;
}

//int main(){
//	GUIinit("��ɭ","2208010132");
//}
