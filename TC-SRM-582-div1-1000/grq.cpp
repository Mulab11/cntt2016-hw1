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

const int N=500005;
int mu[N],vis[N],p[N],tot;
vi g[N],a[N];
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
bool check(int x){
	for(int i=2;i*i<=x;i++)
		if(x%i==0){
			int k=0;
			while(x%i==0)x/=i,k++;
			if(k>=3) return 0;
		}
	return 1;
}
void pre(){
	int n=20000,m=500000;
	memset(vis,0,sizeof(vis));tot=0;
	mu[1]=1;
	for(int i=2;i<=m;i++){
		if(!vis[i]) p[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&p[j]*i<=m;j++){
			vis[p[j]*i]=1;
			if(i%p[j]==0){mu[i*p[j]]=0;break;} else mu[i*p[j]]=-mu[i];
		}
	}
//	printf("%d\n",mu[3]);
	for(int i=1;i<=n;i++) g[i].clear();
	for(int i=1;i<=n;i++){
		if(!mu[i]) continue;
		for(int j=i;j<=n;j+=i) g[j].pb(i);
	}
	for(int i=1;i<=n;i++){
		a[i].clear();
		for(int j=i;j<=m;j+=i)
			if(mu[j]) a[i].pb(j);
	}
}
inline ll sq2(ll x){
	ll l=1,r=3e8;
	while(l<r){
		ll mid=l+r+1>>1;
		if(mid*mid<=x) l=mid; else r=mid-1;
	}
	return r;
}
inline ll sq3(ll x){
	ll l=1,r=500000;
	while(l<r){
		ll mid=l+r+1>>1;
		if(mid*mid*mid<=x) l=mid; else r=mid-1;
	}
	return r;
}
int get(int d,int l,int r){
	if(l>r) return 0;
	return (upper_bound(a[d].begin(),a[d].end(),r)-lower_bound(a[d].begin(),a[d].end(),l))*mu[d];
}
ll solve(ll n){
	pre();
	ll ans=0;
	for(ll a=1;a*a*a<=n;a++){
		if(!mu[a]) continue;
		ans+=max(0ll,sq2(n/a)-a);
	}
	for(ll b=1;b*b*b*b<=n;b++){
		if(!check(b)) continue;
		for(ll k=1;k*k*k<=b;k++){
			ll bp=b/gcd(b,k*k),kp=k*k/gcd(b,k*k);
			if(!mu[bp]) continue;
			for(int i=0;i<g[bp].size();i++)
				ans+=get(g[bp][i],b/kp+1,((int)sq3(n/b))/kp);
		}
	}
	return ans;
}

class SemiPerfectPower{
public:
	long long count(long long L, long long R){
//		printf("%lld %lld\n",solve(R),solve(L-1));
		return solve(R)-solve(L-1);
	}
};
