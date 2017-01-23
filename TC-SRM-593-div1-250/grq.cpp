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

const int u[6][2]={0,-1,0,1,-1,0,1,0,1,-1,-1,1};
bool vis[2505];
vi g[2505];
int col[2505],n,si,cnt;

bool dfs(int x,int y){
	if(vis[x]){
		if(col[x]==y) return 1;
		return 0;
	}
	vis[x]=1;col[x]=y;si++;
	for(int i=0;i<g[x].size();i++)
		if(!dfs(g[x][i],y^1)) return 0;
	return 1;
}

class HexagonalBoard{
public:
	int minColors(vector <string> board){
		n=board.size();cnt=n*n;
		for(int i=0;i<n*n;i++) g[i].clear(),vis[i]=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(board[i][j]=='-'){vis[i*n+j]=1;cnt--;continue;}
				for(int k=0;k<6;k++){
					int x=i+u[k][0],y=j+u[k][1];
					if(x<0||y<0||x>=n||y>=n||board[x][y]=='-') continue;
					g[i*n+j].pb(x*n+y);
				}
			}
		if(!cnt) return 0;
		bool ans=1,con=1;
		for(int i=0;i<n*n;i++)
			if(!vis[i]) si=0,ans&=dfs(i,0),con&=(si<2);
		if(con) return 1;
		if(ans) return 2;
		return 3;
	}
};
