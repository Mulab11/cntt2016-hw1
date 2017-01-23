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

const int N=25,inf=1e9;
int u[4][2]={1,0,0,1,-1,0,0,-1};
int n,m,ans,now[N],a[N][N];
vector<string> b;
void rev(int x,int y){
	if(x<0||y<0||x>=n||y>=m) return;
	a[x][y]^=1;
}
void upt(int x,int y,int t){
	if(t) rev(x,y);
	for(int i=0;i<4;i++) rev(x+u[i][0],y+u[i][1]);
}
void dfs(int x,int cnt){
	if(x==n){
		bool isok=1;
		for(int i=0;i<m;i++) if(!a[n-1][i]) isok=0;
		if(isok) ans=min(ans,cnt);
		return;
	}
	bool vis[2]={0,0};
	for(int i=0;i<m;i++)
		if(!a[x-1][i]&&(~now[i])) vis[now[i]]=1;
	if(vis[0]&&vis[1]) return;
	if(!vis[1]){
		int tmp[N];
		vi g;g.clear();
		memcpy(tmp,now,sizeof(tmp));
		for(int i=0;i<m;i++) if(!a[x-1][i]) g.pb(i),upt(x,i,0),cnt++,now[i]=0;
		dfs(x+1,cnt);cnt-=g.size();
		memcpy(now,tmp,sizeof(now));
		for(int i=0;i<g.size();i++) upt(x,g[i],0);
	}
	if(!vis[0]){
		int tmp[N];
		vi g;g.clear();
		memcpy(tmp,now,sizeof(tmp));
		for(int i=0;i<m;i++) if(!a[x-1][i]) g.pb(i),upt(x,i,1),cnt++,now[i]=1;
		dfs(x+1,cnt);cnt-=g.size();
		memcpy(now,tmp,sizeof(now));
		for(int i=0;i<g.size();i++) upt(x,g[i],1);
	}
}

class YetAnotherBoardGame{
public:
	int minimumMoves(vector<string> board){
		b=board;ans=inf;
		n=b.size();m=b[0].size();
		for(int typ=0;typ<2;typ++)
		for(int i=0;i<(1<<m);i++){
			for(int j=0;j<n;j++)
				for(int k=0;k<m;k++)
					if(b[j][k]=='B') a[j][k]=1; else a[j][k]=0;
			memset(now,-1,sizeof(now));
			int cnt=0;
			for(int j=0;j<m;j++)
				if(i&(1<<j)) upt(0,j,typ),now[j]=typ,cnt++;
			dfs(1,cnt);
		}
		return ans<inf?ans:-1;
	}
};

