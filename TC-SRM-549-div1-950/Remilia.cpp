// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <algorithm>

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

const int inf=1e9;

int n,S,T,idx,ans,tot,Llim,Rlim,bo[11],A[11][11],B[11][11][11],li[11][11],ID[11],g[11],dis[11],p[11],a[11],d[11],D[11];
VI Ed[11];

inline bool bfs(){
	++idx;
	int l=0,r=1;dis[S]=0;ID[S]=idx;
	for(g[l]=S;l<r;){
		int u=g[l++];
		For(v,1,T)if(A[u][v] && ID[v]^idx){
			ID[g[r++]=v]=idx;
			dis[v]=dis[u]+1;
			if(v==T)return 1;
		}
	}
	return 0;
}

int dinic(int u,int ff){
	if(u==T)return ff;
	int res=0;
	For(v,1,T)if(A[u][v] && ID[v]==idx && dis[v]==dis[u]+1){
		int tmp=dinic(v,min(ff,A[u][v]));
		ff-=tmp;res+=tmp;
		A[u][v]-=tmp;A[v][u]+=tmp;
		if(!ff)return res;
	}
	return res?res:(dis[u]=-inf,0);
}

inline int Flow(){
	int ans=0;
	for(;bfs();)ans+=dinic(S,inf);
	return ans;
}
//网络流部分
//===

inline void ck(int c){
	For(i,1,n)d[i]=0;
	For(i,1,n)for(int j:Ed[i])++d[j];//处理每个点的入度
	int xx=0,now=0;
	For(i,1,n)p[i]=i;
	do{
		++now;
		bool flag=1;
		For(i,1,n)D[i]=d[i];
		For(i,1,n)if(D[p[i]]){//如果还有前驱没有被拿过则不合法
			flag=0;
			break;
		}else{
			for(int v:Ed[p[i]])--D[v];
		}
		if(flag)++xx;
		if(xx>Rlim)return;
		if(xx+tot-now<Llim)return;
	}while(next_permutation(p+1,p+n+1));//枚举排列，并判断这个排列是否可行
	++ans;
}

void dfs(int c,int i,int _){
	if(i>n || _==n)return;//爆搜边界
	if(!bo[i]){
		bo[i]=1;
		li[c][++*li[c]]=i;
		if(c>1)rep(s,1,1<<*li[c-1]){//枚举出边
			bool FLAG=1;
			rep(j,0,*li[c-1])if(s>>j&1)Ed[i].pb(li[c-1][j+1]);
			For(k,1,T)For(j,1,T)A[k][j]=0;
			//网络流建图，先把下界引流
			For(j,1,*li[c]){
				int u=li[c][j];
				for(int v:Ed[u]){
					A[u][v]=inf;
					--A[v][T];
				}
			}
			For(k,1,*li[c-1])if((A[li[c-1][k]][T]+=a[li[c-1][k]])<0){
				FLAG=0;
				break;
			}
			For(k,1,*li[c])if((A[S][li[c][k]]=a[li[c][k]]-Ed[li[c][k]].size())<0){
				FLAG=0;
				break;
			}
			//如果可以引流
			if(FLAG){
				int tmp=Flow();
				For(k,1,*li[c])tmp-=a[li[c][k]]-Ed[li[c][k]].size();
				//如果满流则说明合法，进行下一步爆搜
				if(tmp==0){
					if(_==n-1)ck(c);else{
						dfs(c,i+1,_+1);
						*li[c+1]=0;
						dfs(c+1,1,_+1);
					}
				}
			}
			Ed[i].resize(0);
		}else{
			if(_==n-1)ck(c);else{
				dfs(c,i+1,_+1);
				*li[c+1]=0;
				dfs(c+1,1,_+1);
			}
		}
		--*li[c];
		bo[i]=0;
	}
	if(i<n)dfs(c,i+1,_);
}

struct CosmicBlocks{
	int getNumOrders(VI blockTypes, int minWays, int maxWays){
		n=blockTypes.size();
		rep(i,0,n)a[i+1]=blockTypes[i];
		Llim=minWays;
		Rlim=maxWays;
		S=n+1;T=n+2;
		tot=1;For(i,1,n)tot*=i;
		dfs(1,1,0);
		//读入
		return ans;
	}
};