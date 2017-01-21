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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
//#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int inf=1e6+3;
int ub,lb,n,step[15],ans,pos[15],vis[15];
vi b;
bool go[15][15];
map<ll,bool> VIS;
vector<pii> edge,tmp;

//maxflow templet
struct node{
	int to,next,v;
}p[1005];
int S,T,head[25],st[25],tot,du[25];
inline void clear(){
	memset(head,-1,sizeof(head));
	tot=0;S=n+1;T=n+2;
}
inline void add(int x,int y,int z){
	p[tot].to=y;p[tot].next=head[x];p[tot].v=z;head[x]=tot++;
	p[tot].to=x;p[tot].next=head[y];p[tot].v=0;head[y]=tot++;
}
queue<int> q;
inline bool bfs(int x){
	memset(st,0,sizeof(st));
	st[x]=1;q.push(x);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];~i;i=p[i].next){
			int y=p[i].to,v=p[i].v;
			if(!v||st[y]) continue;
			st[y]=st[x]+1;q.push(y);
		}
	}
	return st[T]>0;
}
inline int dfs(int x,int f){
	int r=0;
	if(x==T) return f;
	for(int i=head[x];~i;i=p[i].next){
		int y=p[i].to,v=p[i].v,tmp;
		if(!v||st[y]!=st[x]+1) continue;
		tmp=dfs(y,min(f-r,v));
		r+=tmp;
		p[i].v-=tmp;p[i^1].v+=tmp;
		if(r==f)break;
	}
	if(!r) st[x]=-1;
	return r;
}
inline int dinic(){
	int t,ans=0;
	while(bfs(S)) while(t=dfs(S,inf)) ans+=t;
	return ans;
}

bool check(){
	int vis[15],sum=0;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++) vis[step[i]]++;
	for(int i=0;i<n;i++) if(!vis[i]) break; else sum+=vis[i];
	if(sum!=n) return 0;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++) vis[step[i]]+=b[i];
	for(int i=0;i<n-1;i++) if(vis[i]<vis[i+1]) return 0;
	return 1;
}
int dfs2(int x){
	if(x==n) return 1;
	int ans=0;
	for(int i=0;i<n;i++){
		if(vis[i]) continue;
		bool isok=1;
		for(int j=0;j<x;j++){
			if(go[x][j]&&i<pos[j]){isok=0;break;}
			if(go[j][x]&&i>pos[j]){isok=0;break;}
		}
		if(!isok) continue;
		pos[x]=i;vis[i]=1;
		ans+=dfs2(x+1);
		vis[i]=0;
	}
	return ans;
}
bool solve(int c){
	clear();int need=0;
	vi d;d.clear();
	for(int i=0;i<n;i++) d.pb(b[i]);
	for(int i=0;i<tmp.size();i++)
		if(step[tmp[i].FF]==c) add(tmp[i].FF,tmp[i].SS,inf),d[tmp[i].FF]--,d[tmp[i].SS]--;
	for(int i=0;i<n;i++) if(d[i]<0) return 0;
	for(int i=0;i<n;i++) if(step[i]==c) add(S,i,d[i]); else if(step[i]==c+1) need+=d[i],add(i,T,d[i]);
	if(need!=dinic()) return 0;
	return 1;
}
bool check2(int m){
	for(int j=0;j<n;j++)
		if(step[j]>0&&!du[j]) return 0;
	memset(go,0,sizeof(go));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<tmp.size();i++) go[tmp[i].FF][tmp[i].SS]=1;
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				go[i][j]|=(go[i][k]&go[k][j]);
	ll zt=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(go[i][j]) zt|=(1ll<<(i*n+j));
	if(VIS[zt]) return 0;
	VIS[zt]=1;
	for(int j=0;j<m;j++) if(!solve(j)) return 0;
	int t=dfs2(0);
	if(t<lb||t>ub) return 0;
	return 1;
}

void dfs(int x){
	if(x==n){
		if(!check()) return;
		int m=0;
//		ans++;return;
		for(int i=0;i<n;i++) m=max(m,step[i]);
		edge.clear();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(step[i]==step[j]-1) edge.pb(mp(i,j));
		for(int i=0;i<(1<<edge.size());i++){
			memset(du,0,sizeof(du));tmp.clear();
			for(int j=0;j<edge.size();j++)
				if(i&(1<<j)) tmp.pb(edge[j]),du[edge[j].SS]=1;
			ans+=check2(m);
		}
		return ;
	}
	for(int i=0;i<n;i++)
		step[x]=i,dfs(x+1);
}

class CosmicBlocks{
public:
	int getNumOrders(vector <int> block, int minWays, int maxWays){
		int clo=clock();
		ub=maxWays,lb=minWays;
		b=block;n=b.size();ans=0;
		VIS.clear();
		dfs(0);
		cerr<<clock()-clo<<endl;
//		printf("%d\n",ans);
		return ans;
	}
};
