#include <bits/stdc++.h>

using namespace std;

int tid[55][55],n,d[2505],s[2505],q[2505];
int fst[2505],to[5055],nxt[5055],tt,fl[2505];
void ad(int x,int y){
	nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;
	nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;
}

bool bfs(int p){
	memset(d,0,sizeof d);//到每个点的距离 
	memset(fl,0,sizeof fl);
	d[p]=1;
	int l=0,r=-1;
	for(int i=fst[p];i;i=nxt[i]){
		d[to[i]]=2;
		q[++r]=to[i];
		s[to[i]]=to[i];//哪棵子树 
	}
	while(l<=r){
		int x=q[l++];
		if(d[x]>=4)fl[s[x]]=1; 
		for(int i=fst[x];i;i=nxt[i])
		if(!d[to[i]]){
			d[to[i]]=d[x]+1;
			s[to[i]]=s[x];
			q[++r]=to[i];
		}
	}
	int ret=0;
	for(int i=1;i<=n;++i)ret+=fl[i];//几棵子树的深度大于等于3 
	return ret>=3;
}

class GameInDarknessDiv1 {
public:
	string check(vector <string> field) {
		int wa=0,wb=0;
		for(int i=0;i<field.size();++i)
			for(int j=0;j<field[i].size();++j)
			if(field[i][j]!='#'){
				tid[i][j]=++n;
				if(i&&tid[i-1][j])ad(tid[i-1][j],n);
				if(j&&tid[i][j-1])ad(tid[i][j-1],n);
				if(field[i][j]=='A')wa=n;
				if(field[i][j]=='B')wb=n;
			}
		for(int i=1;i<=n;++i)
			if(bfs(i)&&d[wa]>=d[wb]+2)return "Bob wins";
		//结论：如果存在点p有三棵深度大于等于3的子树而且dist(a,p)>=dist(b,p)+2则Bob赢 
		return "Alice wins";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
