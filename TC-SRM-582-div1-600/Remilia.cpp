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
#define PCC pair<char,char>
#define mod 1000000009
const int maxn=1305;
string c1,c2;
map<PCC,int>mp;
int col[maxn],n,m;
int f[maxn][maxn],g[maxn][maxn],sum[maxn];
int fac[maxn],inv[maxn];
int qpow(int a,int b,int p){
	int ret=1;
	for (;b;b>>=1,a=1ll*a*a%mod) if (b&1) ret=1ll*ret*a%mod;
	return ret;
}

/*
从小到大DP，dp[i][j]表示前i个有j个最终需要被看见的方案数（填在整个长为n的空白数组里）
要求是被看见的那些前面不能有空白格子。
转移就是枚举上一个是啥然后排列数乘进去就好了，可以前缀和。

或者从大到小DP，dp[i][j]表示第一个数是后i个有j个被看见的方案数。
然后下一个要么放前面，贡献+1，要么放后面。
减去颜色相同的答案。
*/

ll val;
class ColorfulBuilding{
public:
	int count(vector<string>color1,vector<string>color2,int L){
		rep(i,0,color1.size()-1) c1+=color1[i];
		rep(i,0,color2.size()-1) c2+=color2[i];
		n=c1.size();
		rep(i,0,n-1){
			if (!mp[mk(c1[i],c2[i])]) mp[mk(c1[i],c2[i])]=col[i+1]=++m;
				else col[i+1]=mp[mk(c1[i],c2[i])];
		}
		fac[0]=1;
		rep(i,1,n) fac[i]=1ll*fac[i-1]*i%mod;
		inv[n]=qpow(fac[n],mod-2,mod);
		drp(i,n-1,0) inv[i]=1ll*inv[i+1]*(i+1)%mod;
		rep(i,1,n) rep(j,1,min(L,i)){
			if (j==1) val=(fac[n-1]+g[col[i]][j])%mod;
			else val=(1ll*sum[j-1]+mod-g[col[i]][j-1]+g[col[i]][j])%mod;
			f[i][j]=1ll*val*inv[n-i]%mod;
			val=1ll*f[i][j]*fac[n-i-1]%mod;
			sum[j]=(sum[j]+val)%mod;
			g[col[i]][j]=(g[col[i]][j]+val)%mod;
		}
		return f[n][L];
	}
};
