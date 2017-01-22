#include <bits/stdc++.h>
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

const int N=55,mod=1e9+9;
struct node{
	int to,next;
}p[N<<2];
int c[N][N],n,k,head[N],du[N],tot;
inline void ch(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}
void add(int x,int y){
	p[++tot]=(node){y,head[x]};head[x]=tot;
	p[++tot]=(node){x,head[y]};head[y]=tot;
	du[x]++;du[y]++;
}

namespace usb{
int dp[N][N][N],tmp[N][N],root,now,si[N];
bool vis[N];
void dfs(int x){
	vis[x]=1;
	si[x]=1;int maxx=0;
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to;
		if(vis[y]) continue;
		dfs(y);
		maxx=max(maxx,si[y]);si[x]+=si[y];
	}
	maxx=max(maxx,n-si[x]);
	if(now>maxx) now=maxx,root=x;
}
void treedp(int x){
	vis[x]=1;
	memset(dp[x],0,sizeof(dp[x]));
	dp[x][0][0]=1;
	si[x]=0;
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to;
		if(vis[y]) continue;
		treedp(y);
		memset(tmp,0,sizeof(tmp));
		for(int l=0;l<=si[x];l++)
			for(int r=0;r<=si[x]-l;r++)
				for(int a=0;a<=si[y];a++)
					for(int b=0;b<=si[y]-a;b++)
						ch(tmp[l+a][r+b],(ll)c[l+a][l]*c[r+b][r]%mod*dp[x][l][r]%mod*dp[y][a][b]%mod);
		memcpy(dp[x],tmp,sizeof(dp[x]));
		si[x]+=si[y];
	}
	si[x]++;
	dp[x][si[x]][0]=dp[x][si[x]-1][0];
	dp[x][0][si[x]]=dp[x][0][si[x]-1];
}
int solve(){
	memset(vis,0,sizeof(vis));
	now=n+1;dfs(1);
	memset(vis,0,sizeof(vis));
	int m=n-k,ans=0;
	treedp(root);ans=dp[root][m][m];
	for(int i=1;i<=n-m*2;i++) ans=(ll)ans*i%mod;
	return ans;
}
};
namespace xhk{
int m,fa[N],si[N],dp[N],root;
bool vis[N],can[N];
void dfs(int x,bool c,int dep){
	vis[x]=1;si[x]=1;
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to;
		if(vis[y]) continue;
		dfs(y,(du[x]<=2||x==root)&c,dep+1);
		si[x]+=si[y];fa[y]=x;
	}
	if(dep==m&&si[x]==k&&c) can[x]=1;
}
void treedp(int x){
	vis[x]=1;si[x]=0;
	dp[x]=1;
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to;
		if(vis[y]) continue;
		treedp(y);
		si[x]+=si[y];
		dp[x]=(ll)dp[x]*dp[y]%mod*c[si[x]][si[y]]%mod;
	}si[x]++;
}
int solve(){
	m=n-k*2+2;int ans=0;
	for(int l=1;l<=n;l++){
		memset(can,0,sizeof(can));
		memset(vis,0,sizeof(vis));
		root=l;fa[l]=0;dfs(l,1,1);
		for(int r=1;r<=n;r++){
			if(l==r||!can[r]) continue;
			memset(vis,0,sizeof(vis));
			int t=r;
			while(t) vis[t]=1,t=fa[t];
			treedp(l);treedp(r);
//			printf("%d %d\n",l,r);
			ch(ans,(ll)dp[l]*dp[r]%mod);
		}
	}
	return ans;
}
};

class InducedSubgraphs{
public:
	int getCount(vector <int> edge1, vector <int> edge2, int K){
		n=edge1.size()+1;k=K;
		if(k==1){
			int ans=1;
			for(int i=1;i<=n;i++) ans=(ll)ans*i%mod;
			return ans;
		}
		for(int i=0;i<=n;i++){
			c[i][0]=c[i][i]=1;
			for(int j=1;j<i;j++)
				c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
		}
		memset(head,0,sizeof(head));tot=0;
		memset(du,0,sizeof(du));
		for(int i=1;i<n;i++) add(edge1[i-1]+1,edge2[i-1]+1);
		if(k*2<=n) return xhk::solve(); 
		return usb::solve();
	}
};
