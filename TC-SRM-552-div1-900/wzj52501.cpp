#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define dwn(i,s,t) for(int i=s;i>=t;i--)
using namespace std;
typedef long long ll;
const int maxn=1000010;
struct HolyNumbers {
	int pri[maxn],cnt,vis[maxn];
	void init(int n) { //get primes in [1,n] 
		rep(i,2,n) {
			if(!vis[i]) pri[++cnt]=i;
			rep(j,1,cnt) {
				if(i*pri[j]>n) break;
				vis[i*pri[j]]=1;
				if(i%pri[j]==0) continue;
			}
		}
	} 
	ll dfs(int c,ll n) { 
		if(c>cnt||pri[c]>n) return 1;
		if((ll)pri[c]*pri[c+1]>n) return upper_bound(pri+c,pri+cnt+1,n)-pri-c+1; // cut the branches
		ll ans=dfs(c+1,n);
		for(ll p=pri[c];p<=n;p*=(ll)pri[c]*pri[c]) ans+=dfs(c+1,n/p);
		return ans;
	}
	ll count(ll n,int mxp) {
		cnt=0;init(mxp);
		return dfs(1,n);
	}
}sol;
