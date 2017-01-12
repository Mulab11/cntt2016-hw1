#include <bits/stdc++.h>

using namespace std;

const int mo=1000000009;
typedef long long LL;
int n,K,fst[555],to[555],nxt[555],tt,f[55][55],sz[55][55],g[55][55][55],c[55][55],ji[55];
void dfs(int x,int fa){//dp预处理子树的方案数 
	if(sz[x][fa])return;
	f[x][fa]=1;
	int cnt=0;
	for(int i=fst[x];i;i=nxt[i])
	if(to[i]!=fa){
		dfs(to[i],x);
		f[x][fa]=LL(f[x][fa])*f[to[i]][x]%mo*c[cnt+sz[to[i]][x]][cnt]%mo;
		cnt+=sz[to[i]][x];
	}
	sz[x][fa]=cnt+1;
}
int work1(){//n>=2k的情况，中间的点成一条链 
	static int dist[55][55];
	memset(dist,0x3f,sizeof dist);
	for(int i=1;i<=n;++i)dist[i][i]=0;
	for(int i=1;i<=n;++i)
		for(int j=fst[i];j;j=nxt[j])dist[i][to[j]]=1;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
			dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);//floyd
	int po=n-2*K+1,ret=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		if(dist[i][j]==po){//寻找链的两端 
			int ii,jj;
			for(int k=fst[i];k;k=nxt[k])if(dist[to[k]][j]==po-1){
				ii=to[k];break;
			}
			for(int k=fst[j];k;k=nxt[k])if(dist[to[k]][i]==po-1){
				jj=to[k];break;
			}
			if(sz[i][ii]==K&&sz[j][jj]==K)//两端各K个点 
				ret=(ret+LL(f[i][ii])*f[j][jj])%mo;//答案直接相乘 
		}
	return ret;
}
int m;
void dfs2(int x,int fa){//dp求前后各用了若干个的方案数 
	g[x][0][0]=1;
	for(int i=fst[x];i;i=nxt[i])
	if(to[i]!=fa){
		dfs2(to[i],x);
		for(int j=m;j>=0;--j)
			for(int k=m;k>=0;--k)
			if(g[x][j][k]){
				for(int jj=0;j+jj<=m;++jj)
					for(int kk=0;k+kk<=m;++kk)
					if(g[to[i]][jj][kk]&&(jj||kk))
						g[x][j+jj][k+kk]=(g[x][j+jj][k+kk]+LL(g[x][j][k])*g[to[i]][jj][kk]%mo*c[j+jj][j]%mo*c[k+kk][k])%mo;
			}
	}
	if(sz[x][fa]<=m){
		int t=sz[x][fa];
		g[x][0][t]=(g[x][0][t]+f[x][fa])%mo;
		g[x][t][0]=(g[x][t][0]+f[x][fa])%mo;
	}
}
int work2(){
	m=n-K;
	int ret=0;
	for(int i=1;i<=n;++i){//枚举根 
		memset(g,0,sizeof g);
		dfs2(i,0);
		ret=(ret+g[i][m][m])%mo;
	}
	return LL(ret)*ji[2*K-n-1]%mo;//中间的点顺序随意，答案乘以阶乘 
}

class InducedSubgraphs {
public:
	int getCount(vector <int> edge1, vector <int> edge2, int k) {
		n=edge1.size()+1;
		K=k;
		for(int i=1,x,y;i<n;++i){
			x=edge1[i-1],y=edge2[i-1];
			++x;++y;
			nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;
			nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;
		}
		c[0][0]=1;
		for(int i=1;i<=50;++i){
			c[i][0]=1;
			for(int j=1;j<=i;++j)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mo;
		}//预处理组合数 
		ji[0]=1;
		for(int i=1;i<=50;++i)ji[i]=LL(ji[i-1])*i%mo;//预处理阶乘 
		if(K==1)return ji[n];//特判 
		else {
			for(int i=1;i<=n;++i)dfs(i,0);
			if(K*2<=n)return work1();
			return work2();
		}
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
