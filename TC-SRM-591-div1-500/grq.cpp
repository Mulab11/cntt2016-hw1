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

int k,g[10],sa[10],sb[10];
ll calc(int a,int b,int c,int d){return (ll)(a*2+c)*(b*2+d);}
void add(int *s,int x,int y){for(int i=1;i<=3;i++) if(g[i-1]+1>=x&&g[i]<=y) s[i]++;}
ll solve(int a,int b,int c,int d){
	ll ans=(ll)(a+(c>0))*(b+(d>0));
	ans+=(ll)(a+(c>k/2))*(b+(d>k/2));
	for(int i=1;i<=3;i++) sa[i]=sb[i]=g[i]=0;
	debug(ans);
	if(c>k/2+1) g[1]=k-c; else if(c>0) g[1]=min(k/2-1,c-1);
	if(d>k/2+1) g[2]=k-d; else if(d>0) g[2]=min(k/2-1,d-1);
	g[3]=k/2-1;sort(g+1,g+4);
	if(c>k/2+1) add(sa,1,k/2-1),add(sa,k-c+1,k/2-1); else add(sa,1,c-1);
	if(d>k/2+1) add(sb,1,k/2-1),add(sb,k-d+1,k/2-1); else add(sb,1,d-1);
	for(int i=1;i<=3;i++) ans+=(ll)(g[i]-g[i-1])*calc(a,b,sa[i],sb[i]);
	return ans;
}

class PyramidSequences{
public:
	long long distinctPairs(int N, int M){
		k=__gcd(N*2-2,M*2-2);
		return solve(N/k,M/k,N%k,M%k);
	}
};
