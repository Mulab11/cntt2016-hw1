// by ξ

#include <bits/stdc++.h>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

int f[17777],mu[17777],H[12345678],*h[17777];

bool sqf[431005],tpf[431005],bo[431005];

VI V[17777],jb[17777];

struct SemiPerfectPower{
	void gao(int x){
		// 生成sqf的约数
		int m=V[x].size();
		f[0]=1;jb[x].pb(1);
		rep(i,1,1<<m){
			f[i]=f[i-(i&-i)]*V[x][31-__builtin_clz(i&-i)];
			jb[x].pb(f[i]);
		}
		if(m==0 && x>1)jb[x].pb(x);
	}
	void pret(){
		// 预处理n^1/3以内的信息
		int m=431000,K=17772;
		bo[1]=1;
		For(i,1,m)sqf[i]=tpf[i]=1;
		For(i,2,m)if(!bo[i])
		for(int j=i+i;j<=m;j+=i){
			bo[j]=1;
			if(j<=K)V[j].pb(i);
			if(j%(i*i)==0)sqf[j]=0;
			if(j%(i*i*i)==0)tpf[j]=0;
		}
		For(i,1,K)gao(i);
		mu[1]=1;
		For(i,1,K)
		for(int j=i+i;j<=K;j+=i)mu[j]-=mu[i];
		h[1]=H;
		For(i,1,K)h[i+1]=h[i]+m/i+1;
		For(i,1,K)
		for(int j=i;j<=m;j+=i)h[i][j/i]=h[i][j/i-1]+sqf[j];
	}
	int Sqrt2(LL n){
		// 二次方根
		int l=0,r=1e9;
		for(;l+1<r;){
			int mm=l+r>>1;
			if(1ll*mm*mm<=n)l=mm;else r=mm;
		}return l;
	}
	int Sqrt3(LL n){
		// 三次方根
		int l=0,r=1e6;
		for(;l+1<r;){
			int mm=l+r>>1;
			if(1ll*mm*mm*mm<=n)l=mm;else r=mm;
		}return l;
	}
	LL calc(LL n){
		// 直接计算ax^2的情况以及by^3的情况，其中by^3的情况里要求不含ax^2的情况，simple容斥即可。
		LL an=0;
		for(int a=1;1ll*a*a*a<n;++a)
			if(sqf[a])an+=Sqrt2(n/a)-a;
		cerr<<an<<endl;
		for(int b=1;1ll*b*b*b*b<n;++b)if(tpf[b])
			for(int k=1;k*k*k<=b;++k){
				int g=__gcd(b,k*k),bb=b/g,kk=k*k/g;
				if(sqf[bb])
				for(int d:jb[bb])
					an+=mu[d]*(h[d][Sqrt3(n/b)/(kk*d)]-h[d][b/(kk*d)]);
			}
		return an;
	}
	LL count(LL L,LL R){
		pret();
		return calc(R)-calc(L-1);
	}
};
