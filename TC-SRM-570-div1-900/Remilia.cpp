// by ξ
// program sky  :)

#include <cstdio>
#include <string>
#include <algorithm>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef pair<int ,int> PII;
typedef int node_Arr[1500];
typedef int edge_Arr[20000];

const int inf=1e9;

int n,m,idx,node,tot,source,sink,S,T,a[33][33],ID[33][33][2],g[1000000];
node_Arr he,bo,dis,inin,pre;
edge_Arr ee,ne,pp,cc;

inline void Add(int u,int v,int e,int c){
	pp[++tot]=v;ne[tot]=he[u];he[u]=tot;ee[tot]=e;cc[tot]=c;
	pp[++tot]=u;ne[tot]=he[v];he[v]=tot;ee[tot]=0;cc[tot]=-c;
}

inline bool spfa(){
	int l=0,r=1;
	bo[g[l]=S]=++idx;
	dis[S]=0;inin[S]=1;
	for(;l<r;){
		int u=g[l++];
		for(int e=he[u];e;e=ne[e])if(ee[e]){
			int v=pp[e];
			if(bo[v]^idx || dis[v]>dis[u]+cc[e]){
				bo[v]=idx;
				dis[v]=dis[u]+cc[e];
				pre[v]=e;
				if(!inin[v])inin[g[r++]=v]=1;
			}
		}inin[u]=0;
	}
	return bo[T]==idx;
}

inline PII Flow(){
	PII an=PII();
	for(;spfa();){
		int mi=inf,tmp=0;
		for(int u=T;u^S;u=pp[pre[u]^1])mi=min(mi,ee[pre[u]]),tmp+=cc[pre[u]];
		for(int u=T;u^S;u=pp[pre[u]^1])ee[pre[u]]-=mi,ee[pre[u]^1]+=mi;
		an.x+=mi;
		an.y+=mi*tmp;
	}
	return an;
}

// 费用流部分

inline int Main(){
	tot=1;
	For(i,1,n)For(j,1,m)rep(k,0,2)ID[i][j][k]=++node;//拆点
	T=++node;
	For(i,1,n)For(j,1,m)if(a[i][j]){
		if(a[i][j]==1){//城镇有人则交换流量需要代价
			Add(ID[i][j][0],ID[i][j][1],1,0);
			Add(ID[i][j][1],ID[i][j][0],1,0);
		}else{
			Add(ID[i][j][0],ID[i][j][1],1,1);
			Add(ID[i][j][1],ID[i][j][0],1,1);
		}
		if(i+j&1){//黑白染色
			Add(S,ID[i][j][0],1,0);++source;
			Add(S,ID[i][j][1],1,0);++source;
			if(i>1)Add(ID[i][j][1],ID[i-1][j][1],1,0);
			if(i<n)Add(ID[i][j][1],ID[i+1][j][1],1,0);
			if(j>1)Add(ID[i][j][0],ID[i][j-1][0],1,0);
			if(j<m)Add(ID[i][j][0],ID[i][j+1][0],1,0);
		}else{
			Add(ID[i][j][0],T,1,0);++sink;
			Add(ID[i][j][1],T,1,0);++sink;
		}
	}
	if(source^sink)return -1;
	PII an=Flow();
	if(an.x^sink)return -1;//判断是否满流
	return an.y;//返回费用
}

struct CurvyonRails{
	int getmin(vector<string> field){
		n=field.size();
		m=field[0].size();
		For(i,1,n)For(j,1,m)if(field[i-1][j-1]=='.'){
			a[i][j]=1;
		}else if(field[i-1][j-1]=='C'){
			a[i][j]=2;
		}
		return Main();
	}
};