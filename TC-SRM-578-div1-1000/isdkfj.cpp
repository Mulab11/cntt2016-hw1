#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;
int f[55][55][55][55],n,col[55];
vector<int>g[55];
int s,t,q[5555],dt[55],fst[55],nxt[5555],to[5555],w[5555],c[5555],p[55],in[55],tt;
void ad(int x,int y,int z,int o){
	nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;w[tt]=z;c[tt]=o;
	nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;w[tt]=0;c[tt]=-o;
}

void dfs(int x,int y,int z){//染色 
	col[x]=z;
	for(int i=0;i<g[x].size();++i)
	if(g[x][i]!=y)dfs(g[x][i],x,z);
}

bool spfa(int&ret){
	int l=0,r=1;q[0]=s;
	memset(dt,0x3f,sizeof dt);dt[s]=0;
	while(l!=r){
		int x=q[l++];in[x]=0;
		if(l==5555)l=0;
		for(int i=fst[x];i;i=nxt[i])
		if(w[i]&&dt[to[i]]>dt[x]+c[i]){
			dt[to[i]]=dt[x]+c[i];
			p[to[i]]=i;
			if(!in[to[i]]){
				q[r++]=to[i];
				in[to[i]]=1;
				if(r==5555)r=0;
			}
		}
	}
	if(dt[t]==inf)return 0;
	ret-=dt[t];
	for(int i=t;i!=s;i=to[p[i]^1]){
		--w[p[i]];
		++w[p[i]^1];
	}
	return 1;
}

int dfs(int a,int fa,int b,int fb){
	if(f[a][fa][b][fb]!=-1)return f[a][fa][b][fb];
	for(int i=0;i<g[a].size();++i)
	if(g[a][i]!=fa)
		for(int j=0;j<g[b].size();++j)
		if(g[b][j]!=fb)dfs(g[a][i],a,g[b][j],b);
	int&ret=f[a][fa][b][fb];
	ret=1;
	tt=1;
	memset(fst,0,sizeof fst);
	for(int i=0;i<g[a].size();++i)
	if(g[a][i]!=fa)
		for(int j=0;j<g[b].size();++j)
		if(g[b][j]!=fb)
		ad(i,j+g[a].size(),1,-f[g[a][i]][a][g[b][j]][b]);
	s=g[a].size()+g[b].size(); t=s+1;
	for(int i=0;i<g[a].size();++i)ad(s,i,1,0);
	for(int i=0;i<g[b].size();++i)ad(i+g[a].size(),t,1,0);//二分图最大权匹配 
	while(spfa(ret));
	return ret;
}

class DeerInZooDivOne {
public:
	int getmax(vector <int> a, vector <int> b) {
		n=a.size()+1;
		int ret=0;
		for(int k=0;k<n-1;++k){//枚举切哪条边 
			memset(f,-1,sizeof f);
			for(int i=0;i<n;++i)g[i].clear();
			for(int i=0,x,y;i<n-1;++i)if(i!=k){
				x=a[i];y=b[i];
				g[x].push_back(y);
				g[y].push_back(x);
			}
			dfs(a[k],b[k],1);
			dfs(b[k],a[k],2);//分成两个联通块 
			for(int a=0;a<n;++a)
			if(col[a]==1)
					for(int b=0;b<n;++b)
					if(col[b]==2)
						ret=max(ret,dfs(a,0,b,0));//更新答案 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
