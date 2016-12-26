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
#define SZ(a) (int(a.size()))
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<LL ,LL> PLL;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;
typedef vector<PLL> VLL;

const LL inf=1e18;

int n;
vector<pair<int,PII> > li[55];
VLL ANS;
LL *dis[55][55],DIS[55][55][111];

inline PLL calc(LL A,LL B){// solve Ax>=B
	if(A==0)return 0>=B?PLL{n,inf}:PLL{0,0};
	if(A>0)return B>=0?PLL{(B+A-1)/A,inf}:PLL{n,inf};
	return B<=0?PLL{n,B/A+1}:PLL{0,0};
}

inline void gao(VLL&A){//求并
	sort(ALL(A));
	VLL res;res.resize(0);
	for(auto it:A){
		if(!SZ(res))res.pb(it);
		else{
			auto ti=*res.rbegin();
			res.pop_back();
			if(ti.y>=it.x)res.pb({ti.x,it.y});
			else res.pb(ti),res.pb(it);
		}
	}
	A.swap(res);
}

inline VLL JIAO(VLL&A,VLL&B){//得到A交B
	VLL res;res.resize(0);
	int i=0;
	rep(j,0,SZ(B))
	for(i?--i:0;i<SZ(A) && A[i].x<B[j].y;++i){
		PLL rs={max(A[i].x,B[j].x),min(A[i].y,B[j].y)};
		if(rs.x<rs.y)res.pb(rs);
	}
	return res;
}

inline void Add(int u,int v,PII it){
	li[u].pb(mk(v,it));// 边权(it.x+it.y*x) from u to v
}

LL Main(){
	For(i,0,n)rep(u,0,n)dis[i][u]=DIS[i][u]+55;
	rep(u,1,n)dis[0][u][0]=-inf;dis[0][0][0]=0;
	//init
	For(i,1,n){
		rep(u,0,n){
			For(k,1-i,i-1)dis[i][u][k]=dis[i-1][u][k];
			dis[i][u][-i]=-inf;
			dis[i][u][i]=-inf;
		}//init
		rep(u,0,n)For(k,1-i,i-1)if(dis[i-1][u][k]!=-inf)
			for(auto it : li[u]){
				int v=it.x;
				auto len=it.y;
				if(dis[i-1][u][k]+len.x>dis[i][v][k+len.y])
					dis[i][v][k+len.y]=dis[i-1][u][k]+len.x;// Bellman-Ford
			}
	}
	ANS.pb({n,inf});
	rep(u,0,n){
		// 对每个点的限制范围求交
		VLL V;V.resize(0);
		For(i,1-n,n-1)if(dis[n-1][u][i]!=-inf){
			PLL res={n,inf};//求并
			For(j,-n,n)if(dis[n][u][j]!=-inf){//求交
				PLL tmp=calc(i-j,dis[n][u][j]-dis[n-1][u][i]);
				res={max(res.x,tmp.x),min(res.y,tmp.y)};
				if(res.x>=res.y)break;
			}
			if(res.x<res.y)V.pb(res);
		}
		gao(V);
		ANS=JIAO(ANS,V);
	}
	LL ans=0;
	for(auto it:ANS){
		if(it.y==inf)return -1;
		ans+=it.y-it.x;
	}//count
	return ans;
}

struct YamanoteLine{
	LL howMany(int N,VI s1,VI t1,VI l1,VI s2,VI t2,VI l2){
		n=N;
		rep(i,0,SZ(s1)){
			int u=s1[i],v=t1[i],L=l1[i];// >=L
			if(u<v)Add(u,v,{L,0});else Add(u,v,{L,-1});
		}
		rep(i,0,SZ(s2)){
			int u=s2[i],v=t2[i],L=l2[i];// <=L
			if(u<v)Add(v,u,{-L,0});else Add(v,u,{-L,1});
		}
		rep(i,1,n)Add(i-1,i,{1,0});
		Add(n-1,0,{1,-1});// additional
		return Main();
	}
};