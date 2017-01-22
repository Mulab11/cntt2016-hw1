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

const int N=100005,M=22*N;
struct cir{int x,y,r;}a[N];
struct node{int to,next;}p[N<<2];
int T,n,m,sg[N],son[N],head[N],root[N],tot;
int c[M][2],si[M],flag[M],dep[M],cnt;
bool vis[N];

void add(int x,int y){
	p[++tot]=(node){y,head[x]};head[x]=tot;
	p[++tot]=(node){x,head[y]};head[y]=tot;
}
void rev(int x,int y){flag[x]^=y;}
void pushdown(int x){
	if(!flag[x]||dep[x]<0) return;
	if(flag[x]&(1<<dep[x])) swap(c[x][0],c[x][1]);
	if(c[x][0]) rev(c[x][0],flag[x]);
	if(c[x][1]) rev(c[x][1],flag[x]);
	flag[x]=0;
}
void update(int x){si[x]=si[c[x][0]]+si[c[x][1]];}

int merge(int x,int y){
	if(!x) return y;if(!y) return x;
	if(dep[x]<0) return x;
	pushdown(x);pushdown(y);
	c[x][0]=merge(c[x][0],c[y][0]);
	c[x][1]=merge(c[x][1],c[y][1]);
	update(x);
	return x;
}
void insert(int &root,int x){
	int k=++cnt;root=k;dep[k]=19;si[k]=1;
	for(int i=19;~i;i--){
		if(x&(1<<i)) c[k][1]=++cnt; else c[k][0]=++cnt;
		si[cnt]=1;dep[cnt]=i-1;k=cnt;
	}
}
int mex(int k,int x){
	int ans=0;
	for(int i=19;~i;i--){
		pushdown(k);
		if(x&(1<<i)){
			if(si[c[k][1]]<(1<<i)) k=c[k][1];
			else k=c[k][0],ans^=1<<i;
		}
		else{
			if(si[c[k][0]]<(1<<i)) k=c[k][0];
			else k=c[k][1],ans^=1<<i;
		}
	}
	return ans;
}
int dfs(int x){
	vis[x]=1;root[x]=son[x]=sg[x]=0;
	insert(root[x],0);
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to;
		if(vis[y]) continue;
		son[x]^=dfs(y);
		root[x]=merge(root[x],root[y]);
	}
	sg[x]=mex(root[x],son[x]);
	rev(root[x],son[x]^sg[x]);
	return sg[x];
}

bool operator < (cir a,cir b){return a.r>=b.r;}
int dis(cir x,cir y){return sqr(x.x-y.x)+sqr(x.y-y.y);}

class CirclesGame{
public:
	string whoCanWin(vector <int> x, vector <int> y, vector <int> r){
		n=x.size();
		for(int i=1;i<=n;i++) head[i]=0,vis[i]=0;tot=0;
		for(int i=n*22;i>=0;i--) c[i][0]=c[i][1]=flag[i]=dep[i]=si[i]=0;
		cnt=0;
		for(int i=0;i<n;i++) a[i+1]=(cir){x[i],y[i],r[i]};
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
			for(int j=i-1;j;j--)
				if(dis(a[i],a[j])<sqr(a[j].r)){add(i,j);break;}
		int ans=0;
		for(int i=1;i<=n;i++) if(!vis[i]) ans^=dfs(i);
		if(ans) return "Alice";
		return "Bob";
	}
};
