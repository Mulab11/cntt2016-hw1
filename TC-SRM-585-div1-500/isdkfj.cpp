#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

class LISNumber {
public:
	static const int mo=1000000007;
	int fa[10005],rf[10005];
	LL ksm(LL x,int k){//快速幂 
		LL r=1;
		for(;k;k>>=1,x=x*x%mo)if(k&1)r=r*x%mo;
		return r;
	}
	LL C(int x,int y){//组合数,c[n][m]=n!/((n-m)!*m!)
		if(x<y)return 0;
		return LL(fa[x])*rf[y]%mo*rf[x-y]%mo;
	}
	int count(vector <int> cardsnum, int K) {
		int N=1296*2;
		fa[0]=1;for(int i=1;i<=N;++i)fa[i]=LL(fa[i-1])*i%mo;
		rf[N]=ksm(fa[N],mo-2);
		for(int i=N-1;i>=0;--i)rf[i]=LL(rf[i+1])*(i+1)%mo;
		//预处理阶乘和阶乘的逆元 
		static int f[1297];
		f[0]=0;
		int s=0,n=cardsnum.size();
		for(int i=0;i<n;++i)s+=cardsnum[i];
		for(int k=1;k<=K;++k){
			LL su=1;
			for(int i=0;i<n;++i)su=su*C(k,cardsnum[i])%mo;
			//求出LISNumber<=k的方案数 
			for(int i=1;i<k;++i)
				if((su-=f[i]*C(s+k-i,k-i)%mo)<0)su+=mo;
			//扣掉<k的方案 
			f[k]=su;
		}
		return f[K];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
