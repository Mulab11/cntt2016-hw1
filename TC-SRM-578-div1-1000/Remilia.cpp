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

typedef int Arr[55];

namespace bip{
	int n,A[55][55];
	Arr lx,ly,vx,vy,slack,mate;
	#define clr(a) For(i,1,n)a[i]=0
	//初始化
	inline void init(int n1,int n2){
		n=max(n1,n2);
		For(i,1,n)For(j,1,n)A[i][j]=0;
		clr(lx);clr(ly);clr(mate);
	}
	//加边
	inline int append(int u,int v,int w){A[u][v]=w;}
	//找交错路
	bool gao(int u){
		vx[u]=1;
		For(v,1,n)if(!vy[v]){
			//在相等子图中
			if(lx[u]+ly[v]==A[u][v]){
				vy[v]=1;
				//找到交错路
				if(!mate[v] || gao(mate[v]))return mate[v]=u,1;
			}else slack[v]=min(slack[v],lx[u]+ly[v]-A[u][v]);
		}return 0;
	}
	inline int KM(){
		For(i,1,n)For(j,1,n)lx[i]=max(lx[i],A[i][j]);
		For(i,1,n){
			For(j,1,n)slack[j]=1e9;
			clr(vx);clr(vy);
			if(!gao(i)){
				//调整顶标
				for(;;){
					int dlt=1e9;
					For(j,1,n)if(!vy[j])dlt=min(dlt,slack[j]);
					For(j,1,n){
						if(vx[j])lx[j]-=dlt;
						if(vy[j])ly[j]+=dlt;else slack[j]-=dlt;
					}
					For(j,1,n)if(!vy[j] && !slack[j]){
						if(!mate[j])goto loop1;
						vy[j]=1;
						if(!vx[mate[j]] && gao(mate[j])){
							mate[j]=0;goto loop1;
						}
					}
				}
				//处理i的匹配点
				loop1:;
				clr(vx);clr(vy);
				gao(i);
			}
		}
		//计算答案
		int an=0;
		For(i,1,n)an+=lx[i]+ly[i];
		return an;
	}
}

int n,Ans,F[55][55];
VI Ed[55];

inline void Link(int u,int v){Ed[u].pb(v);Ed[v].pb(u);}

int calc(int u,int ff,int x,int y,int dan){
	int an=0;
	for(int a:Ed[u])if(a^ff && a^dan)
		for(int b:Ed[x])if(b^y)
			F[b][a]=calc(a,u,b,x,dan);
	//求出儿子之间的答案
	bip::init(Ed[u].size(),Ed[x].size());
	rep(i,0,Ed[u].size())if(Ed[u][i]^ff && Ed[u][i]^dan)
		rep(j,0,Ed[x].size())if(Ed[x][j]^y)
			bip::append(i+1,j+1,F[Ed[x][j]][Ed[u][i]]);
	//二分图最大权匹配
	return an=bip::KM()+1;
}

void DFS(int u,int ff,int x,int y){
	for(int v:Ed[u])if(v^ff)
		DFS(v,u,x,y);
	//枚举另一根鹿角的根
	Ans=max(Ans,calc(u,0,x,y,x));
	//更新答案
}

void dfs(int u,int ff){
	if(ff)DFS(ff,u,u,ff);
	for(int v:Ed[u])if(v^ff)
		dfs(v,u);
	//枚举较深的鹿角的根
}

struct DeerInZooDivOne{
	int getmax(vector <int> a, vector <int> b){
		n=a.size();
		rep(i,0,n)Link(a[i]+1,b[i]+1);
		++n;
		//读入数据
		dfs(1,0);
		return Ans;
	}
};