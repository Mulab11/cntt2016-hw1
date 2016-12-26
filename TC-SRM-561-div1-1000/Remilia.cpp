// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <algorithm>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define pb push_back

using namespace std;

typedef double db;
typedef vector<int> VI;

int n,m,K,bo[2500],sm[2500],dis[2500][2500],ID[2500][2500],g[333];
db eva,ans,binom[333][333];
VI Ed[2500];

inline void Link(int u,int v){Ed[u].pb(v);Ed[v].pb(u);}

void dfs(int u,int ff=0){
	sm[u]=bo[u];
	for(int v:Ed[u])if(v^ff)dfs(v,u),sm[u]+=sm[v];
}

inline void dfss(int u,int *dis,int ff=0){
	for(int v:Ed[u])if(v^ff)
		dis[v]=dis[u]+1,dfss(v,dis,u);
}

void gao(int u,int ff=0){
	for(int v:Ed[u])if(v^ff){
		ans+=1-(binom[sm[v]][K]+binom[sm[1]-sm[v]][K])*eva;
		gao(v,u);
	}
}

inline db Main(){
	dfs(1);
	For(u,1,n)dfss(u,dis[u]);
	For(i,0,m){
		*binom[i]=1;
		For(j,1,i)binom[i][j]=binom[i-1][j-1]+binom[i-1][j];
	}eva=1/binom[m][K];
	gao(1);
	// 期望线性性算每条边在斯坦纳树上的概率
	ans*=2;
	rep(i,1,m)For(j,i+1,m){
		int u=g[i],v=g[j],s=0;
		For(k,1,m)if(k^i && k^j){
			int x=g[k];
			s+=(dis[u][x]<dis[u][v] || dis[u][x]==dis[u][v] && x>v) && (dis[v][x]<dis[v][u] || dis[v][x]==dis[v][u] && x>u);
		}
		ans-=binom[s][K-2]*dis[u][v]*eva;
	}
	// 先把树的直径最小表示
	// 期望线性性算每条链成为直径的概率
	return ans;
}

struct Orienteering{
	db expectedLength(vector<string> field, int K_){
		K=K_;
		int i=0;
		for(auto s:field){
			int j=0;
			for(char c:s){
				if(c!='#'){
					ID[i][j]=++n;
					if(i>0 && ID[i-1][j])Link(n,ID[i-1][j]);
					if(j>0 && ID[i][j-1])Link(n,ID[i][j-1]);
					if(c=='*')bo[ID[i][j]]=1,g[++m]=n;
				}++j;
			}++i;
		}
		// 读入
		return Main();
	}
};