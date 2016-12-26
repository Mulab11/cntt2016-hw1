// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

inline int cg(char c){
	return c<='9'?c-'0':c<='Z'?36+c-'A':10+c-'a';
}

const int inf=1e9,dx[]={1,-1,0,0},dy[]={0,0,1,-1};

int ans,n,m,idx,tot,node,S,T,B[55][55],C[55][55],ID[55][55][2];

typedef int nArr[1000];
typedef int mArr[10000];

nArr he,g,bo,dis;
mArr ne,pp,ee;

inline void Add(int u,int v,int w){
	pp[++tot]=v;ne[tot]=he[u];he[u]=tot;ee[tot]=w;
	pp[++tot]=u;ne[tot]=he[v];he[v]=tot;ee[tot]=0;
}

inline bool bfs(){
	int l=0,r=1;dis[S]=0;
	for(bo[g[l]=S]=++idx;l<r;){
		int u=g[l++];
		for(int e=he[u];e;e=ne[e])if(ee[e]){
			int v=pp[e];
			if(bo[v]<idx){
				bo[v]=idx;
				dis[g[r++]=v]=dis[u]+1;
				if(v==T)return 1;
			}
		}
	}
	return 0;
}

int dinic(int u,int ff){
	if(u==T)return ff;
	int res=0;
	for(int e=he[u];e;e=ne[e])if(ee[e]){
		int v=pp[e];
		if(bo[v]==idx && dis[v]==dis[u]+1){
			int tmp=dinic(v,min(ff,ee[e]));
			ee[e]-=tmp;ee[e^1]+=tmp;
			res+=tmp;ff-=tmp;
			if(!ff)return res;
		}
	}
	return res?res:(dis[u]=-1,0);
}

// maxflow

inline int Main(){
	For(i,1,n)For(j,1,m)rep(k,0,2)ID[i][j][k]=++node;//split points
	T=++node;tot=1;
	For(i,1,n)For(j,1,m)if(i+j&1){//black cell
		int tmp=B[i][j]-C[i][j];//when there is a stone
		Add(ID[i][j][1],ID[i][j][0],inf);
		if(B[i][j]){
			ans+=B[i][j];//when it is dominated
			Add(S,ID[i][j][1],B[i][j]);
		}
		//===
		if(tmp>0){
			ans+=tmp;
			Add(ID[i][j][0],T,tmp);
		}
		if(tmp<0){
			Add(S,ID[i][j][0],-tmp);
		}
		//subtrack
		//===
		rep(d,0,4){//adj
			int x=i+dx[d],y=j+dy[d];
			if(x && x<=n && y && y<=m){
				Add(ID[i][j][0],ID[x][y][1],inf);
				Add(ID[i][j][1],ID[x][y][0],inf);
			}
		}
	}else{//so do white
		int tmp=B[i][j]-C[i][j];
		Add(ID[i][j][0],ID[i][j][1],inf);
		if(B[i][j]){
			ans+=B[i][j];
			Add(ID[i][j][1],T,B[i][j]);
		}
		if(tmp>0){
			ans+=tmp;
			Add(S,ID[i][j][0],tmp);
		}
		if(tmp<0){
			Add(ID[i][j][0],T,-tmp);
		}
	}
	for(;bfs();)ans-=dinic(S,inf);
	return ans;
}

struct SurroundingGame{
	int maxScore(vector<string> cost,vector<string> benefit){
		n=cost.size();
		m=cost[0].size();
		For(i,1,n)For(j,1,m)C[i][j]=cg(cost[i-1][j-1]);
		For(i,1,n)For(j,1,m)B[i][j]=cg(benefit[i-1][j-1]);
		//initilize
		return Main();
	}
};