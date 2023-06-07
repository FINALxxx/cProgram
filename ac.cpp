#include<bits/stdc++.h> 
#include "ac.h"

using namespace std;

int tr0[N][26], idx0;//Trie��:[�ڵ���][�ڵ����ӵĶ�ӦĿ���] 
int e0[N], fail0[N];

void ac_init(){
	memset(tr0,0,sizeof(tr0));
	idx0=0;
	memset(e0,0,sizeof(e0));
	memset(fail0,0,sizeof(fail0));
}

void insert(char *s){
	int p = 0;
    for (int i = 0;s[i]; i++){
        if (!tr0[p][s[i] - 'a']) tr0[p][s[i] - 'a'] = ++idx0;
        p = tr0[p][s[i] - 'a'];
    }
    e0[p]++;
}

queue<int> q;
void bfs(){//��trie������BFS��Ŀ����Ԥ����ʧ��ָ��
	for (int i = 0; i < 26; i++) if (tr0[0][i]) q.push(tr0[0][i]);//push���ڵ������ĵ�һ��ڵ� 
	
	
    while (q.size()){
        int now = q.front();q.pop();
        
        for (int i = 0; i < 26; i++) {
        	if (tr0[now][i]){
        		fail0[tr0[now][i]] = tr0[fail0[now]][i];
				q.push(tr0[now][i]);
			} 
            else tr0[now][i] = tr0[fail0[now]][i];
        }
    }
}
int query(char* t){
    int u = 0, res = 0;
    //cout<<k<<endl;
    for (int k = 0; t[k]; k++) {
    	//cout<<k<<endl;
        u = tr0[u][t[k] - 'a'];  // ת��
        for (int j = u; j && e0[j] != -1; j = fail0[j]) {
            res += e0[j], e0[j] = -1;
        }
    }
    return res;
}

//int main(){
//	ac_automation *ac;
//	//ac->init();
//	char *fname="a&b";
//	char word[40];
//	memset(word,0,sizeof(word));
//	int sidx=0;
//	for(int i=0;i<strlen(fname);i++){
//		if(fname[i]!='&'){
//			word[sidx]=fname[i];
//			sidx++;
//		} 
//		else {
//			ac->insert(word);
//			memset(word,0,sizeof(word));
//			sidx=0;
//		}
//	}
//	ac->insert(word);//��insertһ������Ϊ���һ���������治���&�������Զ�����insert
//	ac->bfs();
//	ac->query(word);
//	
//	return 0;
//}


//int main(){
//		
//		char *fn="a&b&c";
//		//ģ��ƥ�䣬����ac�Զ���
//		
//		int sidx=0;
//		for(int i=0;i<strlen(fn);i++){
//			if(fn[i]!='&'){
//				word[sidx]=fn[i];
//				sidx++;
//			} 
//			else {
//				insert(word);
//				sidx=0;
//			}
//		}
//		insert(word);  
//		bfs();
//		cout<<query("abc");
//		
//	
//	return 0;
//} 
