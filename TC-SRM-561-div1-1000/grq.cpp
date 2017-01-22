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

const int M=2505,N=405,u[4][2]={1,0,0,1,-1,0,0,-1};
const ld eps=1e-9;
struct node{
	int to,next;
}p[M<<3];
int head[M],tot;
void add(int x,int y){
	p[++tot]=(node){y,head[x]};head[x]=tot;
	p[++tot]=(node){x,head[y]};head[y]=tot;
}
vector<string> a;
double ans,p1[M],p2[M],fac[M],res;
int n,k,lab[M],dep[M],si[M],dp[M][13],num[N][N],dis[N][N];
bool vis[M],b[M];

ld carry(vi a,vi b){
	int n=a.size(),l=0,r=0;
	ld ans=1.0;
	for(;;){
		if(r==n) break;
		while(l<n&&ans<1.0) ans*=a[l++];
		if(l==n) break;
		while(r<n&&ans>=1.0) ans/=b[r++];
	}
	while(l<n) ans*=(ld)a[l++];
	while(r<n) ans/=(ld)b[r++];
	return ans;
}
inline void ins(vi &l,int a){
	for(int i=1;i<=a;i++) l.pb(i);
}
double solve(int a,int b,int x,int y){
	vi l,r,L,R;
	l.clear(),r.clear();
	ins(l,a);ins(l,y);ins(l,x-y);
	ins(r,x);ins(r,b);ins(r,a-b);
	return carry(l,r);
}
inline void rise(int &x,int y){
	for(int i=0;i<13;i++)
		if(y&(1<<i)) x=dp[x][i];
}
int lca(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	rise(y,dep[y]-dep[x]);
	if(x==y) return x;
	for(int i=12;i>=0;i--)
		if(dp[x][i]!=dp[y][i]) x=dp[x][i],y=dp[y][i];
	return dp[x][0];
}
void dfs(int x){
	vis[x]=1;si[x]=b[x];
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to;
		if(vis[y]) continue;
		dep[y]=dep[x]+1;dfs(y);
		si[x]+=si[y];dp[y][0]=x;
	}
	if(x!=1&&si[x]>=k) ans-=2*p2[si[x]];
	if(x!=1&&n-si[x]>=k) ans-=2*p2[n-si[x]];
}
inline bool check(int x,int y,int p,int q){
	if(dis[x][y]>dis[p][q]) return 0;
	return dis[x][y]<dis[p][q]||(x>=p&&y>=q);
}
inline void calc(int x,int y){
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(i!=x&&i!=y&&check(x,i,x,y)&&check(i,y,x,y)) cnt++;
	if(cnt<k-2) return;
	ans-=dis[x][y]*p1[cnt];
//	if(p1[cnt]>1e-3) printf("%d %.3f\n",dis[x][y],p1[cnt]);
	res+=p1[cnt];
}

class Orienteering{
public:
	double expectedLength(vector <string> field, int K){
		a=field;
		int h=a.size(),c=a[0].size();
		k=K;int cnt=0;
		memset(num,0,sizeof(num));
		memset(head,0,sizeof(head));
		memset(vis,0,sizeof(vis));tot=0;n=0;
		for(int i=0;i<h;i++)
			for(int j=0;j<c;j++)
				if(a[i][j]!='#'){
					b[num[i][j]=++cnt]=(a[i][j]!='.');
					if(a[i][j]=='*') lab[++n]=cnt;
				}
		for(int i=0;i<h;i++)
			for(int j=0;j<c;j++){
				if(!num[i][j]) continue;
				for(int k=0;k<4;k++){
					int x=i+u[k][0],y=j+u[k][1];
					if(x<0||y<0||x>=h||y>=c||!num[x][y]) continue;
					add(num[i][j],num[x][y]);
				}
			}
		fac[0]=1;
		for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i;
		for(int i=k-2;i<=n;i++) p1[i]=solve(i,k-2,n,k);
		for(int i=k;i<=n;i++) p2[i]=solve(i,k,n,k);
//		debug(cnt);
		ans=(cnt-1)*2.0;
		dep[1]=1;dfs(1);
		for(int j=1;j<13;j++)
			for(int i=1;i<=cnt;i++)
				dp[i][j]=dp[dp[i][j-1]][j-1];
		res=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=dep[lab[i]]+dep[lab[j]]-2*dep[lca(lab[i],lab[j])];
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++) calc(i,j);
		return ans;
	}
};
