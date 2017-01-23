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

const int N=55;
int n,match[N];
string color;
bool go[N][N],vis[N],use[N];

bool dfs(int x){
	for(int y=0;y<n;y++){
		if(!go[x][y]||vis[y]||!use[y]) continue;
		vis[y]=1;
		if(match[y]==-1||dfs(match[y])){match[y]=x;return 1;}
	}
	return 0;
}
int solve(char s,char t){
	for(int i=0;i<n;i++)
		if(color[i]==t) use[i]=1; else use[i]=0;
	int ans=0;
	memset(match,-1,sizeof(match));
	for(int i=0;i<n;i++){
		if(color[i]!=s) continue;
		memset(vis,0,sizeof(vis));
		ans+=dfs(i);
	}
	return ans;
}

class GearsDiv1{
public:
	int getmin(string color, vector <string> graph){
		::color=color;
		n=color.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(graph[i][j]=='Y') go[i][j]=1; else go[i][j]=0;
		return min(min(solve('R','G'),solve('G','B')),solve('B','R'));
	}
};
