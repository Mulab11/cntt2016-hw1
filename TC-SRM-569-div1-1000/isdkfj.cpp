#include <bits/stdc++.h>

using namespace std;

const int mod=1000000009;
const int dx[]={0,0,2,3,2,5,3,7,2,3,5};
const int dy[]={0,0,1,1,2,1,1,1,3,2,1};
typedef long long LL;

int K,mo,B;
LL ksm(LL x,int k){//快速幂 
	LL ret=1;
	for(;k;k>>=1,x=x*x%mo)if(k&1)ret=ret*x%mo;
	return ret;
}
void mul(int(*a)[20],int(*b)[20]){//矩阵乘法 
	static int c[20][20];
	memset(c,0,sizeof c);
	for(int i=1;i<=K;++i)
		for(int k=1;k<=K;++k)
			for(int j=1;j<=K;++j)
			c[i][j]=(c[i][j]+LL(a[i][k])*b[k][j])%mo;
	memcpy(a,c,sizeof c);
}
int a[35][20][20],b[35][20][20],ans[20][20];
int work(int n,int modd){
	mo=modd;
	memset(a,0,sizeof a);
	memset(b,0,sizeof b);
	memset(ans,0,sizeof ans);
	for(int k=0;k<=30;++k){
		for(int i=1;i<K;++i)
			for(int j=i;j<K;++j)a[k][i][j]=1;
		for(int j=1;j<K;++j)a[k][K][j]=k%mo;
		a[k][K][K]=1;//求出含B^k的转移矩阵 
	}
	for(int i=1;i<=K;++i)b[0][i][i]=1;
	for(int k=1;k<=30;++k){
		for(int i=1;i<=K;++i)b[k][i][i]=1;
		for(int i=1;i<B;++i)mul(b[k],b[k-1]),mul(b[k],a[k-1]);
		mul(b[k],b[k-1]);//递推出B^k-1的矩阵 
	}
	for(int k=0;k<=30;++k)mul(b[k],a[k]);//B^k的矩阵 
	int le=0,xs[31];
	while(n){xs[le++]=n%B;n/=B;}//按位分解 
	for(int i=1;i<=K;++i)ans[i][i]=1;
	for(int i=le-1;i>=0;--i)
		for(int j=1;j<=xs[i];++j)mul(ans,b[i]);
	return ans[K][K-1];
}

class MegaFactorial {
public:
	int countTrailingZeros(int N, int K, int B) {
		::K=K+1;::B=dx[B];
		int ret1=work(N,mod),ret2=dy[B]>1?work(N,dy[B]):0;
		mo=mod;
		ret1=(ret1-ret2+mo)%mo;//扣掉余数 
		ret1=ret1*ksm(dy[B],mo-2)%mo;
		return ret1;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
