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
	//自动加载应总是放在system("cls")前面，以便刷新界面 
	if(head==NULL) if(!readInfo(uid,0)) return 0; 
	system("cls");
	return 1;
}

void addNode(string actName,string aid,string actHold,string actCat,string actLimit,string actAdmin){
	node* now=new node(actName,aid,actHold,actCat,actLimit,actAdmin,head->nxt);
	head->nxt=now;
}

void delNode(node* prev,node* it){//删除it节点 
	prev->nxt=it->nxt;
}

void inputInfo(char* uid){
	saveFlag=0;
	string actName,aid,actHold,actCat,actLimit,actAdmin;
	cout<<"输入图书名称：(输入NULL退出)";
	cin>>actName;
	if(!actName.compare("NULL")) return;
	cout<<"输入图书isdn：";
	cin>>aid;
	cout<<"输入图书出版社：";
	cin>>actHold;
	cout<<"输入图书类别：";
	cin>>actCat;
	cout<<"输入图书所在区域：";
	cin>>actLimit;
	cout<<"输入作者：";
	cin>>actAdmin;
	
	if(head==NULL){//头节点为NULL：配置头节点 
		head=new node("",uid,"","","","",NULL); 
	}
	addNode(actName,aid,actHold,actCat,actLimit,actAdmin);
}

void printInfo(char* uid,char* name){
	if(!init(uid)) return;//无用户文件且当前无链表记录 
	
	cout<<"*************************************************\n";
	cout<<"*\t    用户<"<<name<<">的借书信息(粗略)\t\t*\n";
	cout<<"*************************************************\n";
	cout<<"*  序号  *  图书名称  *  图书类型  *  作者  *\n";
	cout<<"*************************************************\n";
	int cnt=1;
	for(node* it=head->nxt;it!=NULL;it=it->nxt){
		printf("*%-8d*%-12s*%-12s*%-12s*\n",cnt++,(it->actName).c_str(),(it->actCat).c_str(),(it->actAdmin).c_str());
		
	}
	cout<<"*************************************************\n";
	cout<<"<<按任意键以退出打印界面>>"; 
	system("pause>nul"); 
}

void saveInfo(char* uid){
	saveFlag=1;
	system("cls");
	cout<<"该操作将覆盖原有文件，确定？(Y/n):";
	char op=getch();
	if(op!='Y'){
		cout<<"\n已取消数据保存\n";
		cout<<"<<按任意键以退出保存界面>>"; 
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
	
	cout<<"\nSEC：数据写入成功\n";
	cout<<"<<按任意键以退出保存界面>>";
	system("pause>nul");
}

bool readInfo(char* uid,bool flag){
	system("cls");
	if(flag){
		cout<<"该操作将在原有文件上追加新内容，确定？(Y/n):";
		char op=getch();
		if(op!='Y'){
			cout<<"\n已取消数据追加\n";
			cout<<"<<按任意键以退出保存界面>>"; 
			system("pause>nul"); 
			return 0;
		}
	}else{
		cout<<"数据未加载，将进行自动加载，确定？(Y/n):";
		char op=getch();
		if(op!='Y'){
			cout<<"\n已取消自动加载\n";
			cout<<"<<按任意键以退出打印界面>>"; 
			system("pause>nul"); 
			return 0;
		}
	}
	
	char path[20];
	sprintf(path,"./%s.dat",uid);
	
	ifstream ifile(path,ios::binary);
	if(!ifile.is_open()){
		cout<<"\nRE：无用户文件\n";
		cout<<"<<按任意键以退出打印界面>>"; 
		system("pause>nul"); 
		return 0; 
	} 
	
	while(!ifile.eof()){
		string rname,raid,rhold,rcat,rlimit,radmin;
		ifile>>rname>>raid>>rhold>>rcat>>rlimit>>radmin;
		if(ifile.eof()) break;
		if(head==NULL){//头节点为NULL：配置头节点 
			head=new node("",uid,"","","","",NULL); 
		}
		addNode(rname,raid,rhold,rcat,rlimit,radmin);
	}
	ifile.close();
	saveFlag=0;
	if(flag){
		cout<<"\nSEC：数据追加成功\n";
		cout<<"<<按任意键以退出保存界面>>";
		system("pause>nul");
	}else{
		cout<<"\nSEC:自动加载完成\n";
		cout<<"<<按任意键以继续操作>>";
		system("pause>nul");
	}
	return 1;
}

void cntInfo(char* uid,char* name){
	if(!init(uid)) return;
	
	int cnt=0;
	for(node* it=head->nxt;it!=NULL;it=it->nxt) cnt++;
	cout<<"*****************************************\n";
	cout<<"*\t   用户<"<<name<<">的借书概览\t\t*\n";
	cout<<"*****************************************\n";
	cout<<"*\t   共有"<<cnt<<"个已经借入的图书   \t*\n";
	cout<<"*****************************************\n";
	cout<<"*\t   共有"<<cnt0<<"个已经归还的图书   \t*\n";
	cout<<"*****************************************\n";
	cout<<"<<按F以搜索活动详细信息>>\n";
	cout<<"<<按其他任意键以退出统计界面>>\n";
	char op=getch();
	if(op=='F'){
		findInfo(uid,name); 
	}else return;
	
} 

bool find(string op,int met,char* fname){//ac_automation
	if(met==0){
		string fn=fname;
		return kmp(op,fn);//模糊匹配，采用kmp-nextval
	}else if(met==1){
		ac_init();
		char word[50];//查询参数串 
		memset(word,0,sizeof(word));
		//模糊匹配，采用ac自动机
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
		insert(word);//多insert一次是因为最后一个参数后面不会跟&，不会自动触发insert
		bfs();
		if(query((char*)op.c_str())) return true;//只要任意匹配中一次就算匹配命中 
	} 	
	else if(met==2){
		if(op.compare(fname)==0) return true;//完全匹配 
	} 

	//失配
	return false; 
}

void findInfo(char* uid,char* name){
	if(!init(uid)) return;
	
	char op,fname[40];int met=0;
	cout<<"(N=按名称/I=按isdn/H=按出版社/C=按图书类型)\n(R=按图书区域/A=按作者/*=全部/其他=取消搜索)\n"; 
	cout<<"请输入搜索类型："; 
	cin>>op; 
	
	cout<<"\n(0=单参数模糊匹配搜索/1=多参数模糊匹配搜索(仅英文)/2=完全匹配搜索)\n";
	cout<<"请输入搜索方式：";
	cin>>met;
	
	cout<<"\n(多参数匹配中每个参数通过&分割)\n";
	cout<<"请输入搜索内容：";
	cin>>fname; 
	
	bool flag=0;
	int cnt=0;
	cout<<"************************************************************************\n";
	cout<<"*\t\t\t用户<"<<name<<">的图书信息(详细)\t\t\t*\n";
	cout<<"************************************************************************\n";
	cout<<"*序号*  图书名称  *  idsn  * 图书类型 * 图书区域 *  出版社  *作者*\n";
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
		if(flag){//匹配成功 
			printf("*%-4d*%-12s*%-7s*%-10s*%-10s*%-12s*%-10s*\n",++cnt,it->actName.c_str(),it->aid.c_str(),it->actCat.c_str(),it->actLimit.c_str(),it->actHold.c_str(),it->actAdmin.c_str());
			cout<<"************************************************************************\n";
		}
	}
	if(cnt==0){//无匹配结果
		cout<<"*\t\t\t\tRE:无匹配结果\t\t\t\t*\n";
		cout<<"************************************************************************\n";
	}else{
		cout<<"*\t\t\t\t共"<<cnt<<"条匹配结果\t\t\t\t*\n";
		cout<<"************************************************************************\n";
	}
	cout<<"<<按任意键退出搜索界面>>";
	system("pause>nul");
}

void modifyInfo(char* uid){
	if(!init(uid)) return;
	
	char sid[20];
	cout<<"请输入待修改图书的唯一isdn：(输入NULL退出)\n";
	cin>>sid;
	if(!strcmp(sid,"NULL")) return;
	
	for(node* it=head->nxt;it!=NULL;it=it->nxt){
		if(find(it->aid,1,sid)){
			cout<<"你现在正在修改图书：\""<<it->actName<<"\"的借入信息\n";
			cout<<"\n(输入NULL以取消修改)\n";
			cout<<"请输入待修改图书的图书名称、出版社、图书类别、所在区域、作者：\n";
			char op[20];
			cin>>op;
			if(strcmp(op,"NULL")==0){
				cout<<"\nSEC：已取消修改操作\n";
				cout<<"<<按任意键退出修改界面>>";
				system("pause>nul");
				return; 
			}
			
			it->actName=op;
			cin>>it->actHold>>it->actCat>>it->actLimit>>it->actAdmin;
			saveFlag=0; 
			cout<<"\nSEC：修改成功\n";
			cout<<"<<按任意键退出修改界面>>";
			system("pause>nul");
			return;
		} 
	}
	//无匹配结果 
	cout<<"\nRE:无匹配结果"; 
}

void removeInfo(char* uid){
	if(!init(uid)) return;
	
	char sid[20];
	cout<<"请输入待归还图书的isdn：(输入NULL退出)\n";
	cin>>sid;
	if(!strcmp(sid,"NULL")) return;
	
	for(node* it=head;it!=NULL;it=it->nxt){
		if(find((it->nxt)->aid,1,sid)){//每次匹配下一个元素的aid 
			cout<<"\n是否归还图书\""<<(it->nxt)->actName<<"\"?(Y/n)：";
			char op; 
			op=getch();
			if(op=='Y'){
				cnt0++;
				cout<<"\nSEC：已归还图书\""<<(it->nxt)->actName<<"\"\n";
				delNode(it,it->nxt); 
				saveFlag=0; 
				cout<<"<<按任意键退出删除界面>>";
				system("pause>nul");
				return; 
			}else{
				cout<<"\n已取消归还操作\n"; 
				cout<<"<<按任意键退出删除界面>>";
				system("pause>nul");
				return; 
			}
			
			
		} 
	}
	//无匹配结果 
	cout<<"\nRE:无匹配结果"; 
	
}

bool quit(){//是否安全退出 
	if(saveFlag) return 1;//修改操作后执行了保存 
	else{
		cout<<"修改信息后未保存，确定退出？(Y/n):";
		char op=getch();
		if(op=='Y') return 1;
		else return 0;
	}
}

//int main(){
//	printInfo("严森");
//} 
