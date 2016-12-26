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

const LL inf=1e18;

int P,m,pr[100],co[100],pc[100];
LL L,R;
VI li[1000010];
vector<LL> an[100];

inline int Pow(int x,int y){
	int z=1;
	for(;y;y>>=1,x*=x)if(y&1)z*=x;
	return z;
}

inline void calc(vector<LL> &an,int p,int c,int P){
	// 生成k^2的序列
	rep(i,0,p)li[1ll*i*i%p].pb(i);
	an.resize(P);
	rep(i,0,P){
		if(li[i%p].size()==0){
			an[i]=inf;
			continue;
		}
		int tmp=1;
		// 暴力求是倍数的位置
		for(int K=0;;(K+=p)%=P){
			for(int t:li[i%p]){
				tmp=1ll*tmp*(i-(K+t)*1ll*(K+t)%P)%P;
				if(tmp==0){
					an[i]=K+t;
					goto loop;
				}
			}
		}
		loop:;
	}
	rep(i,0,p)li[i].resize(0);
}

LL Main(){
	// 分解质因数
	int PP=P;
	for(int i=2;i*i<=PP;++i){
		if(PP%i==0){
			++m;
			pr[m]=i;
			pc[m]=1;
			for(;PP%i==0;PP/=i)++co[m],pc[m]*=i;
		}
	}
	if(PP>1)pr[++m]=PP,co[m]=1,pc[m]=PP;
	// 对每个因子计算答案
	For(i,1,m)
		calc(an[i],pr[i],co[i],pc[i]);
	LL res=0;
	rep(i,0,P){
		LL Q=0;
		For(j,1,m)Q=max(Q,an[j][i%pc[j]]);
		if(Q==inf)continue;
		// 计算[L,R]之间的答案个数
		LL x=Q*Q/P*P+i;
		for(;x<=Q*Q;x+=P);
		if(x>R)continue;
		if(x>=L){
			LL y=R/P*P+i;
			for(;y>R;y-=P);
			res+=(y-x)/P+1;
		}else{
			x=L/P*P+i;
			for(;x<L;x+=P);
			LL y=R/P*P+i;
			for(;y>R;y-=P);
			res+=(y-x)/P+1;
		}
	}
	return res;
}

struct SparseFactorial{
	long long getCount(long long lo, long long hi, long long divisor){
		P=divisor;L=lo;R=hi;
		return Main();
	}
};