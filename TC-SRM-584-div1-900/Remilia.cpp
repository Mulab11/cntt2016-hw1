// by ξ
// program sky  :)

#include <vector>
#include <string>
#include <stdio.h>
#include <cassert>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define SZ(A) (int(A.size()))
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

const int INF=1e6;

int node,jc[111],jcl[111],d[111],g[111],be[111],ID[11][11];
bool vis[111];
VII li[111],Ed[111];

void Add(int u,int v,int w){
	li[v].pb({u,w});
}

int Main(){
	// 最小树形图
	int res=0;
	For(u,1,node){
		int &v=jc[u],&w=jcl[u]=INF;
		for(auto it:li[u]){
			if(it.y<w)w=it.y,v=it.x;
		}
		++d[jc[u]];
		res+=w;
	}
	// 拓扑排序
	*g=0;
	For(u,0,node)if(!d[u])g[++*g]=u;
	for(int i=1;i<=*g;++i){
		int u=g[i];
		if(u && !--d[jc[u]])g[++*g]=jc[u];
	}
	// 无环
	if(*g==node+1)return res;
	For(i,1,*g)vis[g[i]]=1;res=0;
	// 重编号
	int n=0;
	For(u,1,node)if(!be[u]){
		be[u]=++n;
		if(!vis[u]){
			for(int v=jc[u];u^v;v=jc[v])be[v]=n;
		}
	}
	// 缩点
	For(u,1,node)if(vis[u]){
		for(auto it:li[u])Ed[be[u]].pb({be[it.x],it.y});
	}else{
		for(int v=u;!vis[v];v=jc[v]){
			res+=jcl[v];
			vis[v]=1;
			for(auto it:li[v])if(be[it.x]^be[u])Ed[be[u]].pb({be[it.x],it.y-jcl[v]});
		}
	}
	For(u,1,node)li[u].resize(0),li[u].swap(Ed[u]);
	For(u,0,node)d[u]=0,vis[u]=0,be[u]=0;
	node=n;
	return Main()+res;
}

struct FoxTheLinguist{
	int minimalHours(int N,vector<string> ci){
		rep(i,0,N)For(j,0,9)ID[i][j]=++node;
		string ss="";
		for(auto it:ci)ss+=it;
		// 连边：若选了u，花费w即可得到v
		for(int i=0;i<SZ(ss);i+=12){
			int u=ID[ss[i]-'A'][ss[i+1]-'0'];
			int v=ID[ss[i+4]-'A'][ss[i+5]-'0'];
			int w=(ss[i+7]-'0')*1000+(ss[i+8]-'0')*100+(ss[i+9]-'0')*10+ss[i+10]-'0';
			if(u^v)Add(u,v,w);
		}
		// 连边：level0的点可以随便选。
		rep(i,0,N)Add(0,ID[i][0],0),Add(0,ID[i][9],INF);
		// 连边：选了leveli就可以选leveli-1
		rep(i,0,N)For(j,1,9)Add(ID[i][j],ID[i][j-1],0);
		int tmp=Main();
		return tmp>=INF?-1:tmp;
	}
};