// by ξ
// program sky  :)

#include <map>
#include <vector>
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

const int mo=1e9+9;

int n,W,H[55],h[11];
bool vis[11][55];

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}

inline int ha(){
	// hash
	int res=0;
	For(i,1,W)res=(res*233ll+H[i]+1)%1000000007;
	return res;
}

map<int,int>Maps[11];

inline bool ok(int i,int j){
	// if it's ok to place i at j
	For(k,1,W){
		int d=h[i]-abs(j-k);
		if((d>H[k])^vis[i][k])return 0;
	}
	return 1;
}

inline void tr(int i,int j){
	// place i at j
	For(k,1,W)H[k]=max(H[k],h[i]-abs(j-k));
}

int dfs(int i){
	if(i==0)return 1;
	int tmp=ha();
	if(Maps[i].find(tmp)!=Maps[i].end())return Maps[i][tmp];
	int &res=Maps[i][tmp];
	For(j,1,W)if(ok(i,j)){
		// enumarate position and search
		VI hh(W+1,0);
		For(k,1,W)hh[k]=H[k];
		tr(i,j);
		inc(res,dfs(i-1));
		For(k,1,W)H[k]=hh[k];
	}
	return res;
}

struct Mountains{
	int countPlacements(VI h,vector<string> vis){
		n=SZ(h);W=SZ(vis[0]);
		For(i,1,n)::h[i]=h[i-1];
		For(i,1,n)For(j,1,W)::vis[i][j]=vis[i-1][j-1]=='X';
		return dfs(n);
	}
};