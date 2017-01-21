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

const int N=20,M=2000005;
int pw[N],dp[M],n,m,k,sa[N],sb[N],gg;
bool can[M],vis[M];
vector<string> b;
vector<pii> p;
vi c;

int check(int *a){
	int sum=0;
	for(int i=0;i<k;i++) if(a[i]) sum++;
	return sum;
}
bool check2(int *a){
//	for(int i=0;i<k;i++) printf("%d ",a[i]);puts("");
	memset(sa,0,sizeof(sa));
	memset(sb,0,sizeof(sb));
	int sum=0;
	for(int i=0;i<k;i++){
		sa[p[i].FF]+=a[i];sb[p[i].SS]+=a[i];
		sum+=a[i]-1;
	}
	if(sum!=c.size()) return 0;
	for(int i=0;i<n;i++) if(sa[i]&1) return 0;
	for(int j=0;j<m;j++) if(sb[j]&1) return 0;
	return 1;
}
bool pre(int x){
	if(vis[x]) return can[x];
	vis[x]=1;
	int t[N],tx=x;
	memset(t,0,sizeof(t));
	for(int i=k-1;i>=0;i--)
		t[i]=tx/pw[i],tx%=pw[i];
	if(check(t)==k){
//		debug(x);
		can[x]=check2(t);
//		debug(can[x]);
		return can[x];
	}
	can[x]=0;
	for(int i=0;i<k;i++){
		if(!t[i]&&pre(x+pw[i])) can[x]=1;
		if(!t[i]&&pre(x+pw[i]*2)) can[x]=1;
	}
	return can[x];
}
int solve(int x){
	if(vis[x]) return dp[x];
//	debug(x);
	vis[x]=1;
	if(!can[x]) return dp[x]=-1;
	int t[N],tx=x;
	memset(t,0,sizeof(t));
	for(int i=k-1;i>=0;i--)
		t[i]=tx/pw[i],tx%=pw[i];
//	printf("%d %d %d\n",x,check(t),gg);
	if(check(t)==gg){
		dp[x]=0;
		for(int i=0;i<k;i++) if(t[i]==2) dp[x]++;
		return dp[x];
	}
	dp[x]=0;
	for(int i=0;i<k;i++){
		if(t[i]) continue;
		int p=solve(x+pw[i]),q=solve(x+pw[i]*2);
		if(p==-1&&q==-1) continue;
		if(p==-1) dp[x]=max(dp[x],q);
		else if(q==-1) dp[x]=max(dp[x],p);
		else dp[x]=max(dp[x],min(p,q));
	}
	return dp[x];
}

class MagicalHats{
public:
	int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses){
		b=board;c=coins;gg=numGuesses;
//		debug(c.size());
		sort(c.begin(),c.end());int sum[N];
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=c.size();i++) sum[i]=sum[i-1]+c[i-1];
		n=b.size();m=b[0].size();
		pw[0]=1;for(int i=1;i<=15;i++) pw[i]=pw[i-1]*3;
		
		p.clear();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(b[i][j]=='H') p.pb(mp(i,j));
		k=p.size();
		memset(vis,0,sizeof(vis));
		if(!pre(0)) return -1;
		memset(vis,0,sizeof(vis));
		return sum[solve(0)];
	}
};
