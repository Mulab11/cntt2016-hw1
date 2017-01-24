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
struct node{int to,next,c;}p[N*N*5];
int n,tot,head[N],col[N];
bool vis[N];
vi a;

void add(int x,int y,int z){
	p[++tot]=(node){y,head[x],z};head[x]=tot;
	p[++tot]=(node){x,head[y],z};head[y]=tot;
}
bool check(int x,int c){
	if(vis[x]) return col[x]==c;
	vis[x]=1;col[x]=c;
	for(int i=head[x];i;i=p[i].next)
		if(!check(p[i].to,c^p[i].c)) return 0;
	return 1;
}

namespace xhk{
	int m,match[N];
	bool use[N];
	vi b;
	bool dfs(int x){
		if(x==m){
			memset(vis,0,sizeof(vis));
			memset(head,0,sizeof(head));tot=0;
			for(int i=0;i<n;i++){
				if(match[i]<i) continue;
				for(int j=i+1;j<n;j++){
					if(match[j]<j) continue;
					if(match[i]>j&&match[i]<match[j]) add(i,j,1);
				}
			}
			for(int i=0;i<n;i++)
				if(!vis[i]){if(!check(i,0)) return 0;}
			return 1;
		}
		if(use[x]) return dfs(x+1);
		for(int i=x+1;i<m;i++)
			if(!use[i]){
				use[x]=use[i]=1;
				match[b[x]]=b[i];match[b[i]]=b[x];
				if(dfs(x+1)) return 1;
				use[x]=use[i]=0;
			}
		return 0;
	}
	string solve(){
		m=0;memset(match,-1,sizeof(match));
		b.clear();
		for(int i=0;i<n;i++) if(a[i]==-1) m++,b.pb(i);
		for(int i=0;i<n;i++){
			int l=-1,r=-1;
			for(int j=0;j<n;j++)
				if(a[j]==i) r=l,l=j;
			if(l!=-1) match[l]=r,match[r]=l;
		}
		memset(use,0,sizeof(use));
		if(dfs(0)) return "POSSIBLE";
		return "IMPOSSIBLE";
	}
}
namespace bx2k{
	vector<pii> b;
	int m,sum[N];
	bool use[N];
	bool calc(int i,int j){return (i&(1<<j))>0;}
	string solve(){
		m=0;b.clear();
		memset(use,0,sizeof(use));
		for(int i=0;i<n;i++){
			int l=0,r=0;
			for(int j=0;j<n;j++)
				if(a[j]==i) l=r,r=j+1;
			if(l) m++,b.pb(mp(l,r));
			use[l]=use[r]=1;
		}
		sort(b.begin(),b.end());
		sum[0]=0;
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(!use[i]);
		for(int i=0;i<(1<<m);i++){
			memset(vis,0,sizeof(vis));
			memset(head,0,sizeof(head));tot=0;
			bool isok=1;
			for(int j=0;j<m;j++)
				for(int k=j+1;k<m;k++)
					if(calc(i,j)==calc(i,k)&&b[j].SS>b[k].FF&&b[j].SS<b[k].SS) isok=0;
			if(!isok) continue;
			add(0,n,0);
			for(int j=0;j<m;j++){
				int l=b[j].FF,r=b[j].SS;
				add(l-1,l,0);add(r,r-1,0);
				if(calc(i,j)||(sum[r]-sum[l-1])%2==0) add(l,r,0); else add(l,r,1);
			}
			for(int j=0;j<=n;j++)
				if(!vis[j]&&!check(j,0)){isok=0;break;}
			if(isok) return "POSSIBLE";
		}
		return "IMPOSSIBLE";
	}
}

class DisjointSemicircles{
public:
	string getPossibility(vector<int> labels){
		a=labels;n=a.size();
		int m=0;
		for(int i=0;i<n;i++) if(a[i]==-1) m++;
		if(m<=12) return xhk::solve(); 
		return bx2k::solve();
	}
};

