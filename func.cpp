#include<bits/stdc++.h>
#include<conio.h>
#include "func.h"
#include "ac.h"
#include "kmp.h"

using namespace std;

int cnt0; 
node* head=NULL;
bool saveFlag=1;

bool init(char* uid){
	//�Զ�����Ӧ���Ƿ���system("cls")ǰ�棬�Ա�ˢ�½��� 
	if(head==NULL) if(!readInfo(uid,0)) return 0; 
	system("cls");
	return 1;
}

void addNode(string actName,string aid,string actHold,string actCat,string actLimit,string actAdmin){
	node* now=new node(actName,aid,actHold,actCat,actLimit,actAdmin,head->nxt);
	head->nxt=now;
}

void delNode(node* prev,node* it){//ɾ��it�ڵ� 
	prev->nxt=it->nxt;
}

void inputInfo(char* uid){
	saveFlag=0;
	string actName,aid,actHold,actCat,actLimit,actAdmin;
	cout<<"����ͼ�����ƣ�(����NULL�˳�)";
	cin>>actName;
	if(!actName.compare("NULL")) return;
	cout<<"����ͼ��isdn��";
	cin>>aid;
	cout<<"����ͼ������磺";
	cin>>actHold;
	cout<<"����ͼ�����";
	cin>>actCat;
	cout<<"����ͼ����������";
	cin>>actLimit;
	cout<<"�������ߣ�";
	cin>>actAdmin;
	
	if(head==NULL){//ͷ�ڵ�ΪNULL������ͷ�ڵ� 
		head=new node("",uid,"","","","",NULL); 
	}
	addNode(actName,aid,actHold,actCat,actLimit,actAdmin);
}

void printInfo(char* uid,char* name){
	if(!init(uid)) return;//���û��ļ��ҵ�ǰ�������¼ 
	
	cout<<"*************************************************\n";
	cout<<"*\t    �û�<"<<name<<">�Ľ�����Ϣ(����)\t\t*\n";
	cout<<"*************************************************\n";
	cout<<"*  ���  *  ͼ������  *  ͼ������  *  ����  *\n";
	cout<<"*************************************************\n";
	int cnt=1;
	for(node* it=head->nxt;it!=NULL;it=it->nxt){
		printf("*%-8d*%-12s*%-12s*%-12s*\n",cnt++,(it->actName).c_str(),(it->actCat).c_str(),(it->actAdmin).c_str());
		
	}
	cout<<"*************************************************\n";
	cout<<"<<����������˳���ӡ����>>"; 
	system("pause>nul"); 
}

void saveInfo(char* uid){
	saveFlag=1;
	system("cls");
	cout<<"�ò���������ԭ���ļ���ȷ����(Y/n):";
	char op=getch();
	if(op!='Y'){
		cout<<"\n��ȡ�����ݱ���\n";
		cout<<"<<����������˳��������>>"; 
		system("pause>nul"); 
		return;
	}

	char path[20];
	sprintf(path,"./%s.dat",uid);

	ofstream ofile(path,ios::binary);
	for(node* it=head->nxt;it!=NULL;it=it->nxt){
		ofile<<it->actName<<" "<<it->aid<<" "<<it->actHold<<" "<<it->actCat<<" "<<it->actLimit<<" "<<it->actAdmin<<endl;
	}
	ofile.close();
	
	cout<<"\nSEC������д��ɹ�\n";
	cout<<"<<����������˳��������>>";
	system("pause>nul");
}

bool readInfo(char* uid,bool flag){
	system("cls");
	if(flag){
		cout<<"�ò�������ԭ���ļ���׷�������ݣ�ȷ����(Y/n):";
		char op=getch();
		if(op!='Y'){
			cout<<"\n��ȡ������׷��\n";
			cout<<"<<����������˳��������>>"; 
			system("pause>nul"); 
			return 0;
		}
	}else{
		cout<<"����δ���أ��������Զ����أ�ȷ����(Y/n):";
		char op=getch();
		if(op!='Y'){
			cout<<"\n��ȡ���Զ�����\n";
			cout<<"<<����������˳���ӡ����>>"; 
			system("pause>nul"); 
			return 0;
		}
	}
	
	char path[20];
	sprintf(path,"./%s.dat",uid);
	
	ifstream ifile(path,ios::binary);
	if(!ifile.is_open()){
		cout<<"\nRE�����û��ļ�\n";
		cout<<"<<����������˳���ӡ����>>"; 
		system("pause>nul"); 
		return 0; 
	} 
	
	while(!ifile.eof()){
		string rname,raid,rhold,rcat,rlimit,radmin;
		ifile>>rname>>raid>>rhold>>rcat>>rlimit>>radmin;
		if(ifile.eof()) break;
		if(head==NULL){//ͷ�ڵ�ΪNULL������ͷ�ڵ� 
			head=new node("",uid,"","","","",NULL); 
		}
		addNode(rname,raid,rhold,rcat,rlimit,radmin);
	}
	ifile.close();
	saveFlag=0;
	if(flag){
		cout<<"\nSEC������׷�ӳɹ�\n";
		cout<<"<<����������˳��������>>";
		system("pause>nul");
	}else{
		cout<<"\nSEC:�Զ��������\n";
		cout<<"<<��������Լ�������>>";
		system("pause>nul");
	}
	return 1;
}

void cntInfo(char* uid,char* name){
	if(!init(uid)) return;
	
	int cnt=0;
	for(node* it=head->nxt;it!=NULL;it=it->nxt) cnt++;
	cout<<"*****************************************\n";
	cout<<"*\t   �û�<"<<name<<">�Ľ������\t\t*\n";
	cout<<"*****************************************\n";
	cout<<"*\t   ����"<<cnt<<"���Ѿ������ͼ��   \t*\n";
	cout<<"*****************************************\n";
	cout<<"*\t   ����"<<cnt0<<"���Ѿ��黹��ͼ��   \t*\n";
	cout<<"*****************************************\n";
	cout<<"<<��F���������ϸ��Ϣ>>\n";
	cout<<"<<��������������˳�ͳ�ƽ���>>\n";
	char op=getch();
	if(op=='F'){
		findInfo(uid,name); 
	}else return;
	
} 

bool find(string op,int met,char* fname){//ac_automation
	if(met==0){
		string fn=fname;
		return kmp(op,fn);//ģ��ƥ�䣬����kmp-nextval
	}else if(met==1){
		ac_init();
		char word[50];//��ѯ������ 
		memset(word,0,sizeof(word));
		//ģ��ƥ�䣬����ac�Զ���
		int sidx=0;
		for(int i=0;i<strlen(fname);i++){
			if(fname[i]!='&'){
				word[sidx]=fname[i];
				sidx++;
			} 
			else {
				insert(word);
				memset(word,0,sizeof(word));
				sidx=0;
			}
		}
		insert(word);//��insertһ������Ϊ���һ���������治���&�������Զ�����insert
		bfs();
		if(query((char*)op.c_str())) return true;//ֻҪ����ƥ����һ�ξ���ƥ������ 
	} 	
	else if(met==2){
		if(op.compare(fname)==0) return true;//��ȫƥ�� 
	} 

	//ʧ��
	return false; 
}

void findInfo(char* uid,char* name){
	if(!init(uid)) return;
	
	char op,fname[40];int met=0;
	cout<<"(N=������/I=��isdn/H=��������/C=��ͼ������)\n(R=��ͼ������/A=������/*=ȫ��/����=ȡ������)\n"; 
	cout<<"�������������ͣ�"; 
	cin>>op; 
	
	cout<<"\n(0=������ģ��ƥ������/1=�����ģ��ƥ������(��Ӣ��)/2=��ȫƥ������)\n";
	cout<<"������������ʽ��";
	cin>>met;
	
	cout<<"\n(�����ƥ����ÿ������ͨ��&�ָ�)\n";
	cout<<"�������������ݣ�";
	cin>>fname; 
	
	bool flag=0;
	int cnt=0;
	cout<<"************************************************************************\n";
	cout<<"*\t\t\t�û�<"<<name<<">��ͼ����Ϣ(��ϸ)\t\t\t*\n";
	cout<<"************************************************************************\n";
	cout<<"*���*  ͼ������  *  idsn  * ͼ������ * ͼ������ *  ������  *����*\n";
	cout<<"************************************************************************\n";
	for(node* it=head->nxt;it!=NULL;it=it->nxt){
		switch(op){
			case'N':flag=find(it->actName,met,fname);break;
			case'I':flag=find(it->actHold,met,fname);break;
			case'H':flag=find(it->actCat,met,fname);break;
			case'C':flag=find(it->actLimit,met,fname);break;
			case'R':flag=find(it->aid,met,fname);break;
			case'A':flag=find(it->actAdmin,met,fname);break;
			case'*':flag=1;break;
			default:return;
		}
		if(flag){//ƥ��ɹ� 
			printf("*%-4d*%-12s*%-7s*%-10s*%-10s*%-12s*%-10s*\n",++cnt,it->actName.c_str(),it->aid.c_str(),it->actCat.c_str(),it->actLimit.c_str(),it->actHold.c_str(),it->actAdmin.c_str());
			cout<<"************************************************************************\n";
		}
	}
	if(cnt==0){//��ƥ����
		cout<<"*\t\t\t\tRE:��ƥ����\t\t\t\t*\n";
		cout<<"************************************************************************\n";
	}else{
		cout<<"*\t\t\t\t��"<<cnt<<"��ƥ����\t\t\t\t*\n";
		cout<<"************************************************************************\n";
	}
	cout<<"<<��������˳���������>>";
	system("pause>nul");
}

void modifyInfo(char* uid){
	if(!init(uid)) return;
	
	char sid[20];
	cout<<"��������޸�ͼ���Ψһisdn��(����NULL�˳�)\n";
	cin>>sid;
	if(!strcmp(sid,"NULL")) return;
	
	for(node* it=head->nxt;it!=NULL;it=it->nxt){
		if(find(it->aid,1,sid)){
			cout<<"�����������޸�ͼ�飺\""<<it->actName<<"\"�Ľ�����Ϣ\n";
			cout<<"\n(����NULL��ȡ���޸�)\n";
			cout<<"��������޸�ͼ���ͼ�����ơ������硢ͼ����������������ߣ�\n";
			char op[20];
			cin>>op;
			if(strcmp(op,"NULL")==0){
				cout<<"\nSEC����ȡ���޸Ĳ���\n";
				cout<<"<<��������˳��޸Ľ���>>";
				system("pause>nul");
				return; 
			}
			
			it->actName=op;
			cin>>it->actHold>>it->actCat>>it->actLimit>>it->actAdmin;
			saveFlag=0; 
			cout<<"\nSEC���޸ĳɹ�\n";
			cout<<"<<��������˳��޸Ľ���>>";
			system("pause>nul");
			return;
		} 
	}
	//��ƥ���� 
	cout<<"\nRE:��ƥ����"; 
}

void removeInfo(char* uid){
	if(!init(uid)) return;
	
	char sid[20];
	cout<<"��������黹ͼ���isdn��(����NULL�˳�)\n";
	cin>>sid;
	if(!strcmp(sid,"NULL")) return;
	
	for(node* it=head;it!=NULL;it=it->nxt){
		if(find((it->nxt)->aid,1,sid)){//ÿ��ƥ����һ��Ԫ�ص�aid 
			cout<<"\n�Ƿ�黹ͼ��\""<<(it->nxt)->actName<<"\"?(Y/n)��";
			char op; 
			op=getch();
			if(op=='Y'){
				cnt0++;
				cout<<"\nSEC���ѹ黹ͼ��\""<<(it->nxt)->actName<<"\"\n";
				delNode(it,it->nxt); 
				saveFlag=0; 
				cout<<"<<��������˳�ɾ������>>";
				system("pause>nul");
				return; 
			}else{
				cout<<"\n��ȡ���黹����\n"; 
				cout<<"<<��������˳�ɾ������>>";
				system("pause>nul");
				return; 
			}
			
			
		} 
	}
	//��ƥ���� 
	cout<<"\nRE:��ƥ����"; 
	
}

bool quit(){//�Ƿ�ȫ�˳� 
	if(saveFlag) return 1;//�޸Ĳ�����ִ���˱��� 
	else{
		cout<<"�޸���Ϣ��δ���棬ȷ���˳���(Y/n):";
		char op=getch();
		if(op=='Y') return 1;
		else return 0;
	}
}

//int main(){
//	printInfo("��ɭ");
//} 
