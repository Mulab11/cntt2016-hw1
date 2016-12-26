// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define SZ(A) (int(A.size()))
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

const int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int n,m,N,dp[2][55][55],deg[55][55],be[55][55],ld[55*55],rd[55*55],lu[55*55],ru[55*55],up[55*55],dn[55*55];
bool A[55][55],vis[55][55];

void dfs(int i,int j){
	if(vis[i][j])return;vis[i][j]=1;
	// 所属的连通块
	be[i][j]=N;
	// 连通块上下边界
	if(up[N]==-1 || i<up[N])up[N]=i;
	if(dn[N]==-1 || i>dn[N])dn[N]=i;
	// 连通块左右上下边界
	if(j==1){
		if(ld[N]==-1 || i>ld[N])ld[N]=i;
		if(lu[N]==-1 || i<lu[N])lu[N]=i;
	}
	if(j==m){
		if(rd[N]==-1 || i>rd[N])rd[N]=i;
		if(ru[N]==-1 || i<ru[N])ru[N]=i;
	}
	// 遍历四联通点
	rep(d,0,4){
		int x=i+dir[d][0],y=j+dir[d][1];
		if(x && y && x<=n && y<=m && A[x][y])dfs(x,y),++deg[i][j];
	}
}

void init(){
	//初始化
	For(i,1,n)For(j,1,m)if(!vis[i][j] && A[i][j]){
		++N;
		ld[N]=lu[N]=rd[N]=ru[N]=up[N]=dn[N]=-1;
		dfs(i,j);
	}
}

bool heng(int i){
	// 是否是整个横行
	if(!A[i][1])return 0;
	int u=be[i][1];
	return ~ld[u] && ~rd[u] && up[u]==dn[u];
}

// 更新最大值
void upd(int &x,int y){if(y>x)x=y;}

bool jin(int i,int j){
	// 是否一定要进入
	if(i==1 || !A[i][j] || j!=1 && j!=m || deg[i][j]==2)return 0;
	return i==up[be[i][j]];
}

bool chu(int i,int j){
	// 是否可以出来
	if(!A[i][j] || j!=1 && j!=m || deg[i][j]==2)return 0;
	if(i^dn[be[i][j]])return 0;
	if(i==1)return 1;
	if(be[i-1][j]==be[i][j] && deg[i-1][j]==1)return i==2;
	return 1;
}

int DP(){
	// dp表示能够并的最大次数
	memset(dp[0],-1,sizeof dp[0]);
	dp[0][0][0]=0;
	For(i,1,n){
		int p=i&1^1,q=p^1;
		memset(dp[q],-1,sizeof dp[q]);
		rep(j,0,i)rep(k,0,i)if(~dp[p][j][k]){
			int xx=dp[p][j][k];
			if(heng(i)){
				// 横行的两种更新
				upd(dp[q][max(j-1,0)][k+1],xx+(j>0));
				upd(dp[q][j+1][max(k-1,0)],xx+(k>0));
			}else{
				// 出入情况四种更新
				if(jin(i,1))
					if(jin(i,m))
						upd(dp[q][max(j-1,0)][max(k-1,0)],xx+(j>0)+(k>0));
					else
						upd(dp[q][max(j-1,0)][k+chu(i,m)],xx+(j>0));
					else if(jin(i,m))
						upd(dp[q][j+chu(i,1)][max(k-1,0)],xx+(k>0));
					else
						upd(dp[q][j+chu(i,1)][k+chu(i,m)],xx);
			}
		}
	}
	// 最大合并次数
	int ans=0;
	For(j,0,n)For(k,0,n)if(dp[n&1][j][k]>0){
		upd(ans,dp[n&1][j][k]);
	}
	return N-ans;
}

int Main(){
	init();
	// 特判n=1,m=1
	if(n==1)return N;
	if(m==1)return !!N;
	return DP();
}

struct Tunnels{
	int minimumTunnels(vector<string> frame){
		n=SZ(frame);m=SZ(frame[0]);
		For(i,1,n)For(j,1,m)
			A[i][j]=frame[i-1][j-1]=='X';
		return Main();
	}
};