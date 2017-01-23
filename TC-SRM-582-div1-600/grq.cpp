#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=1606,mod=1e9+9;
int n,cnt,col[N],dp[N],sum[N][N],s[N];
int fac[N],ifac[N];
string c1,c2;
map<string,int> c;

inline int exp(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=(ll)ans*x%mod;
		x=(ll)x*x%mod;y>>=1;
	}return ans;
}
inline void ch(int &x,int y){x+=y;if(x>=mod) x-=mod;}

class ColorfulBuilding{
public:
	int count(vector<string> color1, vector<string> color2, int L){
		c1=c2="";c.clear();cnt=0;
		for(int i=0;i<color1.size();i++) c1+=color1[i],c2+=color2[i];
		n=c1.size();
		for(int i=0;i<n;i++){
			string t="";t+=c1[i];t+=c2[i];
			if(!c[t]) c[t]=++cnt;
			col[i]=c[t];
		}
		fac[0]=1;ifac[0]=1;
		for(int i=1;i<=n;i++)fac[i]=(ll)fac[i-1]*i%mod,ifac[i]=exp(fac[i],mod-2);
//		for(int i=0;i<n;i++) printf("%d ",col[i]);puts("");
		
		memset(dp,0,sizeof(dp));
		memset(sum,0,sizeof(sum));
		memset(s,0,sizeof(s));
		sum[col[n-1]][1]=s[1]=dp[1]=1;
		for(int i=n-2;~i;i--){
			memset(dp,0,sizeof(dp));
			for(int j=1;j<=n;j++)
				dp[j]=(ll)((sum[col[i]][j]+s[j-1])%mod-sum[col[i]][j-1]+mod)%mod*fac[n-i-2]%mod;
			for(int j=1;j<=n;j++)
				ch(sum[col[i]][j],(ll)dp[j]*ifac[n-i-1]%mod),ch(s[j],(ll)dp[j]*ifac[n-i-1]%mod);
		}
		return (ll)s[L]*fac[n-1]%mod;
	}
};
