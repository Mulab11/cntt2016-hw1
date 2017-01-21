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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;
const int N=1000005;
int p[N],tot;
bool vis[N];
void pre(int n){
	memset(vis,0,sizeof(vis));
	tot=0;
	for(int i=2;i<=n;i++){
		if(vis[i]) continue;
		p[++tot]=i;
		for(int j=i+i;j<=n;j+=i) vis[j]=1;
	}
}
ll dfs(int x,ll n){
	if(x>tot||n<p[x]) return 1;
	if((ll)p[x]*p[x]>n)
		return upper_bound(p+1,p+tot+1,n)-p-x+1;
	ll ans=dfs(x+1,n);
	for(ll k=p[x];k<=n;k=k*p[x]*p[x])
		ans+=dfs(x+1,n/k);
	return ans;
}
class HolyNumbers{
public:
	long long count(long long upTo, int maximalPrime){
		pre(maximalPrime);
//		debuge;
		return dfs(1,upTo);
	}
};
