// by ξ

#include <bits/stdc++.h>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define sqr(x) (x)*(x)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> PDD;
typedef vector<int> VI;
typedef vector<PII> VII;
typedef int Arr[2000006];

const int p=1e9+7;

struct LittleElephantAndBoard{
	int N,B,G,R;
	Arr pw,fac,Invfac;
	int Pow(int x,int y){
		int z=1;
		for(;y>>=1;x=1ll*x*x%p)if(y&1)z=1ll*z*x%p;
		return z;
	}
	int Inv(int x){return Pow(x,p-2);}
	// 组合数
	int Binom(int N,int M){
		if(M>N)return 0;
		return 1ll*fac[N]*Invfac[M]%p*Invfac[N-M]%p;
	}
	void inc(int&x,int y){if((x+=y)>=p)x-=p;}
	// 预处理阶乘逆元和乘方
	void pret(){
		*fac=1;
		For(i,1,N*2)fac[i]=1ll*fac[i-1]*i%p;
		Invfac[N*2]=Inv(fac[N*2]);
		for(int i=N*2;i;--i)Invfac[i-1]=1ll*Invfac[i]*i%p;
		*pw=1;
		For(i,1,N*2)pw[i]=pw[i-1]*2%p;
	}
	// 奇数段的分别有a和b个，插板
	int gao(int n,int m,int a,int b){
		int re=0;
		for(int i=n&1;i<=m;i+=2){
			int rem=n-i-(m-i)*2;if(rem<0)continue;
			rem>>=1;
			int x=a-b+i;if(x&1 || x<0)continue;
			x>>=1;
			inc(re,1ll*Binom(m,i)*Binom(rem+m-1,m-1)%p*Binom(i,x)%p*pw[m-i]%p);
		}
		return re;
	}
	int getNumber(int mm,int rr,int gg,int bb){
		N=mm;
		if(rr+gg+bb!=N*2)return 0;
		B=N-bb;G=N-gg;R=N-rr;
		pret();
		int an=0;
		inc(an,gao(N-B,B-1,G,R));//x..x
		inc(an,gao(N-B,B,G,R)*2%p);//..x..x & x..x..
		inc(an,gao(N-B,B+1,G,R));//..x..x..
		return an*2%p;
	}
};
