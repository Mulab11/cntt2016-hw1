// BEGIN CUT HERE

// END CUT HERE
#line 5 "WolfPack.cpp"
#include <bits/stdc++.h>
#define ll long long
#define P 1000000007

using namespace std;
int fast_pow(int x,int y){
	int ret=1;
	while (y){
		if (y&1) ret=1LL*ret*x%P;
		x=1LL*x*x%P;
		y>>=1;
	}
	return ret;
}

const int maxn=100005;
int fact[maxn],inv[maxn];
void init(int n){
	for (int i=fact[0]=1;i<=n;++i) fact[i]=1LL*fact[i-1]*i%P;
	for (int i=0;i<=n;++i) inv[i]=fast_pow(fact[i],P-2);
}
int c(int n,int m){
	if (m<0||m>n) return 0;
	return 1LL*fact[n]*inv[m]%P*inv[n-m]%P;
}
#define inc(x,y) if(((x)+=(y))>=P)x-=P

class WolfPack{
	int a[66],n;
	int doit(int l,int r,int m){
		int ret=0;
		for (int j=l-m-(a[0]&1);j<=r+m;j+=2){
			int now=1;
			for (int i=0;i<n;++i)
				now=1LL*now*c(m,(m-abs(j-a[i]))/2)%P;
			inc(ret,now);
		}
		return ret;
	}
	public:
	int calc(vector <int> x, vector <int> y, int m){
		init(m);
		n=x.size();
		for (int i=0;i<n;++i){
			a[i]=x[i]+y[i]+(2e5);
			if (i&&(a[i]&1)!=(a[i-1]&1)) return 0;
		}
		int ret=doit(0,4e5,m);
		for (int i=0;i<n;++i) a[i]=x[i]-y[i]+(2e5);
		ret=1LL*ret*doit(0,4e5,m)%P;
		return ret;
	}
};
