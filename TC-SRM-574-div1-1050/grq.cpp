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

const int N=55,inf=1000;
vector<string> a;
int u[4][2]={1,0,0,1,-1,0,0,-1};
int n,m,ans,b[N][N],f[N][2],dp[2][N][N];
bool vis[N][N];

void upt(int &x,int y){
	if(x<y) x=y;
}
bool cnt(int x,int y){
	if(x<0||y<0||x>=n||y>=m) return 0;
	return a[x][y]!='.';
}
int check(int x,int y){
	return cnt(x-1,y)+cnt(x+1,y)+cnt(x,y-1)+cnt(x,y+1);
}

void bfs(int x,int y){
	if(vis[x][y]||a[x][y]=='.') return;
	if(check(x,y)>=2) return;
	ans++;
	int sx=x,sy=y;
	for(;;){
		vis[x][y]=1;bool isok=0;
		for(int i=0;i<4;i++){
			int tx=x+u[i][0],ty=y+u[i][1];
			if(!cnt(tx,ty)||vis[tx][ty]) continue;
			x=tx,y=ty;
			isok=1;break;
		}
		if(!isok) break;
	}
	if(!x){
		if(!sy) f[sx][0]=2;
		if(sy==m-1) f[sx][1]=2;
		return;
	}
	if(!sy) f[sx][0]=1;
	if(sy==m-1) f[sx][1]=1;
	
	if(x==sx&&y==sy) return;
	if(!y){
		if(x-sx>1||!sx||sy!=y) f[x][0]=2;
	}
	if(y==m-1){
		if(x==sx&&!sy) f[x][0]=f[x][1]=-1;
		else if(x-sx>1||sy!=y||!sx) f[x][1]=2;
	}
}

class Tunnels{
public:
	int minimumTunnels(vector<string> frame){
		a=frame;ans=0;
		memset(f,0,sizeof(f));
		memset(vis,0,sizeof(vis));
		n=a.size();m=a[0].size();
		for(int i=0;i<n;i++)
			bfs(i,0),bfs(i,m-1);
		for(int i=0;i<n;i++)
			for(int j=1;j<m-1;j++)
				bfs(i,j);
//		return ans;
		if(m==1) return ans>0;
//		puts("");
//		for(int i=0;i<n;i++) printf("%d %d\n",f[i][0],f[i][1]);
		int res=0,k=0;
		for(int a=0;a<=n;a++)
			for(int b=0;b<=n;b++)
				dp[k][a][b]=-inf;
		dp[k][0][0]=0;
		for(int i=0;i<n;i++){
			k^=1;
			for(int a=0;a<=n;a++)
				for(int b=0;b<=n;b++)
					dp[k][a][b]=-inf;
			for(int a=0;a<=n;a++)
				for(int b=0;b<=n;b++){
					if(dp[k^1][a][b]<0) continue;
					if(f[i][0]==-1&&f[i][1]==-1){
						if(a) upt(dp[k][a-1][b+1],dp[k^1][a][b]+1); else upt(dp[k][a][b+1],dp[k^1][a][b]);
						if(b) upt(dp[k][a+1][b-1],dp[k^1][a][b]+1); else upt(dp[k][a+1][b],dp[k^1][a][b]);
					}
					else{
						int ta=a+(f[i][0]==2),tb=b+(f[i][1]==2);
						bool lx=(f[i][0]==1),rx=(f[i][1]==1);
						if(!a&&!b) upt(dp[k][ta][tb],dp[k^1][a][b]);
						else if(a&&!b) upt(dp[k][ta-lx][tb],dp[k^1][a][b]+lx);
						else if(!a&&b) upt(dp[k][ta][tb-rx],dp[k^1][a][b]+rx);
						else upt(dp[k][ta-lx][tb-rx],dp[k^1][a][b]+lx+rx);
					}
				}
		}
		for(int a=0;a<=n;a++) for(int b=0;b<=n;b++) res=max(res,dp[k][a][b]);
		return ans-res;
	}
};

