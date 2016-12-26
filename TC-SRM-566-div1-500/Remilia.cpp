#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>

using namespace std;
#define mod 1000000007

/*
搞个DP,dp[i][j]表示前i步模n为j的答案
n为一个单位矩乘一下就好了
*/

const int maxn=355;
int f[maxn][maxn],g[maxn],h[maxn],t[maxn],ans[maxn];
int qpow(int a,int b){
	int ret=1;
	for (;b;b>>=1,a=1ll*a*a%mod) if (b&1) ret=1ll*ret*a%mod;
	return ret;
}
int n;
void upd(int &x,ll y){
	x=(y+x)%mod;
}
void multi(int *x,int *y,int *z){
	memset(t,0,sizeof t);
	rep(i,0,n-1) rep(j,0,n-1) upd(t[(i+j)%n],1ll*x[i]*y[j]);
	memcpy(z,t,sizeof t);
}
void qpow(ll x){
	ans[0]=1;
	for (;x;x>>=1,multi(h,h,h)) if (x&1) multi(ans,h,ans);
}
struct PenguinEmperor{
	int countJourneys(int n,ll m){
		::n=n;
		f[0][0]=1;
		rep(i,1,n-1) rep(j,0,n-1){
			upd(f[i][(j+i)%n],f[i-1][j]);
			if ((j+i)%n!=(j+n-i)%n) upd(f[i][(j+n-i)%n],f[i-1][j]);
		}
		memcpy(g,f[m%n],sizeof f[m%n]);
		memcpy(h,f[n-1],sizeof f[n-1]);
		qpow(m/n);
		multi(ans,g,ans);
		return ans[0];
	}
};
