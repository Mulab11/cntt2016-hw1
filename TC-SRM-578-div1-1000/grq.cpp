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

const int N=55,inf=1e5;
namespace km{
int n,mx[N],my[N],pre[N],q[N],w[N][N],wx[N],wy[N],sla[N];
bool vx[N],vy[N];

inline void aug(int x){
	for(int i=x;i;){
		int t=mx[pre[i]];
		my[i]=pre[i],mx[pre[i]]=i;
		i=t;
	}
}
inline void bfs(int x){
	int h=1,t=1;q[t]=x;
	while(1){
		while(h<=t){
			int x=q[h];h++;vx[x]=1;
			for(int i=1;i<=n;i++){
				if(vy[i]) continue;
				if(wx[x]+wy[i]>w[x][i]){
					if(sla[i]>=wx[x]+wy[i]-w[x][i]) sla[i]=wx[x]+wy[i]-w[x][i],pre[i]=x;
					continue;
				}
				pre[i]=x;
				if(!my[i]){aug(i);return;}
				vy[i]=1;q[++t]=my[i];
			}
		}
		int tmp=inf;
		for(int i=1;i<=n;i++) if(!vy[i]) tmp=min(tmp,sla[i]);
		for(int i=1;i<=n;i++) if(vx[i]) wx[i]-=tmp;
		for(int i=1;i<=n;i++) if(vy[i]) wy[i]+=tmp; else sla[i]-=tmp;
		for(int i=1;i<=n;i++){
			if(vy[i]||sla[i]) continue;
			if(!my[i]){aug(i);return;}
			vy[i]=1;q[++t]=my[i];
		}
	}
}

int solve(int nl,int nr,vi a,vi b,vi c){
	n=max(nl,nr);
	for(int i=1;i<=n;i++){
		wx[i]=wy[i]=mx[i]=my[i]=0;
		for(int j=1;j<=n;j++) w[i][j]=0;
	}
	int m=a.size();
	for(int i=0;i<m;i++){
		int x=a[i],y=b[i],z=c[i];
		w[x][y]=max(w[x][y],z);
		wx[x]=max(wx[x],z);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) vx[j]=vy[j]=0,sla[j]=inf;
		bfs(i);
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans+=w[i][mx[i]];
	return ans;
}	
}

struct node{int to,next;}p[N<<2];
int n,fa[N],head[N],tot,dp[N][N][N][N];
inline int find(int x){
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
inline void add(int x,int y){
	p[++tot]=(node){y,head[x]};head[x]=tot;
	p[++tot]=(node){x,head[y]};head[y]=tot;
	fa[find(x)]=find(y);
}

int f(int x,int fx,int y,int fy){
	int &ans=dp[x][fx][y][fy];
	if(~ans) return ans;
	ans=1;
	int nl=0,nr=0;
	
	vi a,b,c;
	a.clear();b.clear();c.clear();
	for(int i=head[x];i;i=p[i].next){
		int sx=p[i].to;
		if(sx==fx) continue;
		nl++;nr=0;
		for(int j=head[y];j;j=p[j].next){
			int sy=p[j].to;
			if(sy==fy) continue;
			nr++;
			a.pb(nl);b.pb(nr);c.pb(f(sx,x,sy,y));
		}
	}
	if(nl&&nr) ans+=km::solve(nl,nr,a,b,c);
	return ans;
}
void clear(int x,int fx,int y,int fy){
	int &ans=dp[x][fx][y][fy];
	if(ans==-1) return;
	ans=-1;
	for(int i=head[x];i;i=p[i].next){
		int sx=p[i].to;
		if(sx==fx) continue;
		for(int j=head[y];j;j=p[j].next){
			int sy=p[j].to;
			if(sy==fy) continue;
			clear(sx,x,sy,y);
		}
	}
}

class DeerInZooDivOne{
public:
	int getmax(vector<int> a, vector<int> b){
		n=a.size()+1;
		int ans=0;
		for(int i=0;i<a.size();i++) a[i]++,b[i]++;
		memset(dp,-1,sizeof(dp));
		for(int i=0;i<a.size();i++){
			memset(head,0,sizeof(head));tot=0;
			for(int j=1;j<=n;j++) fa[j]=j;
			for(int j=0;j<a.size();j++) if(i!=j) add(a[j],b[j]);
			for(int x=1;x<=n;x++)
				for(int y=1;y<=n;y++)
					if(find(x)!=find(y)) ans=max(ans,f(x,0,y,0));
			for(int x=1;x<=n;x++)
				for(int y=1;y<=n;y++)
					if(find(x)!=find(y)) clear(x,0,y,0);
		}
		return ans;
	}
};
