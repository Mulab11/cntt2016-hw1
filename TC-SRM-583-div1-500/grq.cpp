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

const int N=55,inf=1e9;
int n,dp[N][N],tmp[N];
vi g[N],s[N],imp[N];
bool vis[N];

inline void add(int x,int y,int a,int b){
	g[x].pb(y);s[x].pb(a);imp[x].pb(b);
	g[y].pb(x);s[y].pb(a);imp[y].pb(b);
}

inline int dfs(int x){
	vis[x]=1;
	for(int i=0;i<=n;i++) dp[x][i]=inf;
	dp[x][0]=0;
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i],a=s[x][i],b=imp[x][i];
		if(vis[y]) continue;
		dfs(y,a,b);
	}
}

class TurnOnLamps{
public:
	int minimize(vector<int> roads, string initState, string isImportant){
		n=roads.size();
		for(int i=0;i<=n;i++) vis[i]=0,g[i].clear(),s[i].clear(),imp[i].clear();
		for(int i=0;i<n;i++) add(roads[i],i+1,initState[i]=='1',isImportant[i]=='1');
		dfs(0);
		return dp[0][0];
	}
};
