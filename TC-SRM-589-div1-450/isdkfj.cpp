#include <bits/stdc++.h>

using namespace std;

int col[55],fst[55],to[5555],nxt[5555],w[5555],tt,q[55],d[55],s,t;

void ad(int x,int y,int z){
	nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;w[tt]=z;
	nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;w[tt]=0;
}
void clr(){tt=1;memset(fst,0,sizeof fst);}//清空数组 
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
	for(int i=fst[x];i;i=nxt[i])
	if(d[to[i]]==d[x]+1&&(f=dfs(to[i],min(a,w[i])))){
		r+=f;a-=f;
		w[i]-=f;w[i^1]+=f;
	}
	return r;
}
int orz(){//网络流 
	int t=0;
	while(bfs())t+=dfs(s,0x3f3f3f3f);
	return t;
}

class GearsDiv1 {
public:
	int getmin(string color, vector <string> graph) {
		int n=color.size();
		for(int i=0;i<n;++i){
			if(color[i]=='R')col[i]=0;
			if(color[i]=='G')col[i]=1;
			if(color[i]=='B')col[i]=2;
		}
		int ret=998244353;
		for(int id=0;id<3;++id){//枚举哪种颜色顺时针 
			clr();
			s=n;t=n+1;
			int t1=(id+1)%3,t2=(id+2)%3;//剩下的两种 
			for(int i=0;i<n;++i)
			if(col[i]==t1)
				for(int j=0;j<n;++j)
				if(col[j]==t2&&graph[i][j]=='Y')ad(i,j,1);//建边 
			for(int i=0;i<n;++i)if(col[i]==t1)ad(s,i,1);
			else if(col[i]==t2)ad(i,t,1);
			ret=min(ret,orz());//网络流 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
