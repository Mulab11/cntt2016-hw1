// by ξ
// program sky  :)

#include <vector>
#include <complex>
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
typedef complex<db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

int ans,w;

bool ok(int n,int x){
	if(x==n && x%w==0)return 1;
	if(x==n && n<w)return 1;
	if(x==w-1 && n<2*w-1)return 1;
	if(x==0 && n<w)return 1;
	return 0;
}

void dfs(int n,int x,int st){
	// 不用动
	if(n==0){
		if(st<ans)ans=st;
		return;
	}
	if(st+1>=ans)return;
	// 一步完成
	if(ok(n,x)){
		ans=st+1;
		return;
	}
	if(st+2>=ans)return;
	int i=x/w,j=x%w,ii=n/w,jj=n%w;
	// 删掉整个后面
	if(ii>i){
		dfs((i+1)*w-1,x,st+1);
	}
	// 删掉上方一个子矩形
	For(a,1,i)For(b,1,w)dfs(n-a*b,x-a*b,st+1);
	// 左侧矩形延伸到底层
	For(a,1,i+1)For(b,1,j){
		dfs(n-(a+ii-i-1)*b-min(b,jj+1),x-a*b,st+1);
	}
	// 右侧矩形延伸到底层
	For(a,1,i)For(b,1,w-1-j){
		dfs(n-(a+ii-i)*b-min(b,max(0,jj-j)),x-a*b,st+1);
	}
}

struct FoxAndAvatar{
	int minimalSteps(int n, int w, int x){
		::w=w;
		if(w==1){
			if(x!=1)++ans;
			if(x!=n)++ans;
			return ans;
		}
		ans=4;
		dfs(n-1,x-1,0);
		return ans;
	}
};