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

const int mod=1e9+9;
map<vi,int> dp[20];
vi h;
vector<string> v;
int w,n;

int dfs(int x,vi now){
	if(x==n) return 1;
	if(dp[x].find(now)!=dp[x].end()) return dp[x][now];
	dp[x][now]=0;
	int &ans=dp[x][now];
	for(int i=0;i<w;i++){
		if(v[x][i]=='-'&&h[x]>now[i]) continue;
		bool isok=1;
		for(int j=0;j<w;j++){
			int t=h[x]-abs(i-j);
			if(t<=now[j]&&v[x][j]=='X'){isok=0;break;}
			else if(t>now[j]&&v[x][j]=='-'){isok=0;break;}
		}
		if(isok){
			vi tmp=now;
			for(int j=0;j<w;j++) tmp[j]=max(tmp[j],h[x]-abs(i-j));
			ans=(ans+dfs(x+1,tmp))%mod;
		}
	}
	return ans;
}

class Mountains{
public:
	int countPlacements(vector<int> heights, vector<string> visibility){
		h=heights;v=visibility;
		reverse(h.begin(),h.end());
		reverse(v.begin(),v.end());
		w=v[0].size();n=h.size();
//		debug(n);debug(w);
		vi a;a.clear();
		for(int i=0;i<n;i++)dp[i].clear();
		for(int i=0;i<w;i++) a.pb(0);
//		return 0;
		return dfs(0,a);
	}
};

