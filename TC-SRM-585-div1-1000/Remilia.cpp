// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cassert>
#include <algorithm>

#define cp const ww&
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

int n,m,L[400000],R[400000];
LL sr[400000];

struct ww{
	int x,y;
	ww operator - (ww A){return {x-A.x,y-A.y};}
	LL operator ^ (cp A){return 1ll*x*A.y-1ll*y*A.x;}
}P[400000],Q[22];

bool ok(ww A,ww B){
	// 是否所有点在向量AB的左侧
	rep(i,0,m)if(((B-A)^(Q[i]-A))<0)return 0;
	return 1;
}

LL SUMR(int l,int r){
	// R数组的区间和
	if(l==0)return sr[r];
	return sr[r]-sr[l-1];
}

LL Main(){
	LL ans=0;
	// 单调性处理L,R表示左右的合法区间
	rep(i,0,n){
		int &l=L[i],&r=R[i];
		if(i==0)l=r=1;else l=L[i-1],r=R[i-1];
		for(;r+1<n && ok(P[i],P[r+1]);++r);
		for(;l^i && !ok(P[l],P[i]);(++l)%=n);
	}
	sr[0]=R[0];
	rep(i,1,n)sr[i]=sr[i-1]+R[i];
	// 枚举编号最小的点计算答案
	rep(i,0,n)if(L[i]>i){
		int l,r;
		// 特判所有点共线的情况
		if(L[i]==R[i]){
			ans+=n-1-L[i];
			r=R[i]-1;
		}else r=R[i];
		l=max(L[L[i]],i+1);
		if(l<=r){
			ans+=SUMR(l,r)+(1ll-L[i])*(r-l+1);
		}
	}
	return ans;
}

struct EnclosingTriangle{
	LL getNumber(int m,VI x,VI y){
		rep(i,0,m)P[i]={i,0};
		rep(i,0,m)P[i+m]={m,i};
		rep(i,0,m)P[i+2*m]={m-i,m};
		rep(i,0,m)P[i+3*m]={0,m-i};
		n=4*m;
		::m=SZ(x);
		rep(i,0,::m)Q[i]={x[i],y[i]};
		return Main();
	}
};