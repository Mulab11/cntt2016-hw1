#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;
int fst[2005],cur[2005],nxt[1000005],to[1000005],w[1000005],tt=1,s,t,q[20005],d[2005];

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

class FoxAndCity {
public:
	int minimalCost(vector <string> linked, vector <int> want) {
		int n=linked.size();s=n*(n+1)+1;t=s+1;
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
			if(linked[i][j]=='Y')
				for(int k=1;k<=n;++k)
				ad(i*(n+1)+k+1,j*(n+1)+k,inf);//最小割建图 
		for(int i=0;i<n;++i){
			ad(s,i*(n+1)+1,inf);
			for(int j=0;j<n;++j)ad(i*(n+1)+j+1,i*(n+1)+j+2,(want[i]-j)*(want[i]-j));//往后连代价 
			ad(i*(n+1)+n+1,t,(want[i]-n)*(want[i]-n));
			if(i==0)for(int j=1;j<=n;++j)ad(i*(n+1)+j+1,t,inf);//a_0=0
			else ad(s,i*(n+1)+2,inf);//如果i不为0则a_i不为0 
		}
		return orz();
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
