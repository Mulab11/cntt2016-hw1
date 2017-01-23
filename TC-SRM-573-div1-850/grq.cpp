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

const int N=200005,mod=1e9+7;
int n,fac[N],ifac[N];
vi a,b;

void ch(int &x,int y){x+=y;if(x>=mod) x-=mod;}
int exp(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=(ll)ans*x%mod;
		x=(ll)x*x%mod;y>>=1;
	}
	return ans;
}
void pre(){
	int n=100000;
	fac[0]=1;ifac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=(ll)fac[i-1]*i%mod;
	ifac[n]=exp(fac[n],mod-2);
	for(int i=n-1;i;i--) ifac[i]=(ll)ifac[i+1]*(i+1)%mod;
}
int C(int x,int y){
	if(x<y) return 0;
	return (ll)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
int solve(vi a,int m){
	sort(a.begin(),a.end());
	int l=a[n-1]-m,r=a[0]+m,ans=0;
	for(int i=l;i<=r;i++){
		bool isok=1;
		int res=1;
		for(int j=0;j<n;j++){
			int use=abs(i-a[j]);
			if((use+m)&1){isok=0;break;}
			res=(ll)res*C(m,(m-use)/2)%mod;
		}
		if(isok) ch(ans,res);
	}
	return ans;
}

class WolfPack{
public:
	int calc(vector<int> x, vector<int> y, int m){
		pre();
		n=x.size();a.clear();b.clear();
		for(int i=0;i<n;i++) a.pb(x[i]+y[i]),b.pb(x[i]-y[i]);
		return (ll)solve(a,m)*solve(b,m)%mod;
	}
};
