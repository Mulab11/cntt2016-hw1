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

int n,si[55],maxx;
bool g[55][55],vis[55];
void dfs(int x){
	vis[x]=1;maxx=max(maxx,si[x]);
	for(int i=0;i<26;i++){
		if(vis[i]||!g[x][i]) continue;
		dfs(i);
	}
}

class GooseTattarrattatDiv1{
public:
	int getmin(string S){
		n=S.length();
		memset(vis,0,sizeof(vis));
		memset(g,0,sizeof(g));
		memset(si,0,sizeof(si));
		for(int i=0;i<n;i++)
			g[S[i]-'a'][S[n-i-1]-'a']=1,si[S[i]-'a']++;
		int ans=n;
		for(int i=0;i<26;i++)
			if(!vis[i])	maxx=0,dfs(i),ans-=maxx;
		return ans;
	}
};
