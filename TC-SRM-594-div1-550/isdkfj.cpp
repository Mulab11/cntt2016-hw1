#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;
int fst[2505],cur[2505],nxt[1000005],to[1000005],w[1000005],tt=1,s,t,q[2505],d[2505];

void ad(int x,int y,int z){//加边 
	nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;w[tt]=z;
	nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;w[tt]=0;
}
bool bfs(){//bfs
	int l=0,r=0;q[0]=s;
	memset(d,0,sizeof d);d[s]=1;
	while(l<=r){
		int x=q[l++];
		for(int i=fst[x];i;i=nxt[i])
			if(w[i]&&!d[to[i]])d[q[++r]=to[i]]=d[x]+1;
	}
	return d[t];
}
int dfs(int x,int a){//dfs
	if(x==t||a==0)return a;
	int f,r=0;
	for(int&i=cur[x];i;i=nxt[i])//当前弧优化 
	if(d[to[i]]==d[x]+1&&(f=dfs(to[i],min(a,w[i])))){
		r+=f;a-=f;
		w[i]-=f;w[i^1]+=f;
	}
	return r;
}
int orz(){//网络流 
	int t=0;
	while(bfs()){
		memcpy(cur,fst,sizeof fst);
		t+=dfs(s,inf);
	}
	return t;
}

class FoxAndGo3 {
public:
	int maxEmptyCells(vector <string> board) {
		int n=board.size();s=n*n;t=s+1;
		int ret=0;
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j){
				int x=i*n+j;
				if(board[i][j]=='.'){
					ad(s,x,1);
					if(i&&board[i-1][j]=='o')ad(x,x-n,1);
					if(i+1<n&&board[i+1][j]=='o')ad(x,x+n,1);
					if(j&&board[i][j-1]=='o')ad(x,x-1,1);
					if(j+1<n&&board[i][j+1]=='o')ad(x,x+1,1);
					++ret;
				}
				if(board[i][j]=='o')ad(x,t,1),++ret;//最小割建图 
			}
		ret-=orz();
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
