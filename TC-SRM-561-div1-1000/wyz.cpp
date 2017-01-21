// BEGIN CUT HERE

// END CUT HERE
#line 5 "Orienteering.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=605;
namespace vtree{
	struct edge{
		int adj,next,len;
		edge(){}
		edge(int _adj,int _next,int _len):adj(_adj),next(_next),len(_len){}
	} e[maxn*2];
	int n,g[maxn],m;
	void AddEdge(int u,int v,int w){
//		printf("%d %d %d\n",u,v,w);
		e[++m]=edge(v,g[u],w);g[u]=m;
		e[++m]=edge(u,g[v],w);g[v]=m;
	}
	int c;
	void clear(){
		memset(g,0,sizeof(g));m=1;
		n=0;
	}
	int K;
	
	bool vis[maxn];
	double dp[maxn][maxn];
	int size[maxn];
	
	void dfs0(int u,double &res){
		vis[u]=1;
		size[u]=(u<=c);
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (vis[v]) continue;
			dfs0(v,res);
			size[u]+=size[v];
			double p=0,tmp=1;
			for (int k=0;k<K;++k) tmp*=1.0*(size[v]-k)/(c-k);
			p+=tmp;
			tmp=1;
			for (int k=0;k<K;++k) tmp*=1.0*(c-size[v]-k)/(c-k);
			p+=tmp;
//			for (int k=0;k<K;++k) p/=c-k;
//			printf("%d %d %d %d %.3f\n",u,v,e[i].len,size[v],p);
			res+=(1.0-p)*e[i].len;
		}
		vis[u]=0;
	}
	
	int stk[maxn],top;
	int depth[maxn];
	int rt,ed,sum;
	void solve(int u,int root,int d){
		if (depth[root]+d>depth[ed]) return;
		if (depth[root]+d==depth[ed]&&u<ed) return;
		if (depth[ed]-depth[root]+d>depth[ed]) return;
		if (depth[ed]-depth[root]+d==depth[ed]&&u<rt) return;
		if (u<=c) ++sum;
		vis[u]=1;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (vis[v]) continue;
			solve(v,root,d+e[i].len);
		}
		if (u!=root) vis[u]=0;
	}
	
	void dfs1(int u,double &res){
//		printf("in:%d\n",u);
		vis[u]=1;
		stk[top++]=u;
		if (u<=c&&u>rt){
			sum=0;
			ed=u;
			for (int i=1;i<top-1;++i)
				solve(stk[i],stk[i],0);
			double p=1.0*K*(K-1)/(c-K+2)/(c-K+1);
			for (int k=0;k<K-2;++k) p*=1.0*(sum-k)/(c-k);
//			for (int k=0;k<K;++k) p/=c-k;
			res-=p*depth[ed];
//			printf("%d %d %d %.3f\n",rt,ed,sum,p);
		}
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (vis[v]) continue;
			depth[v]=depth[u]+e[i].len;
			dfs1(v,res);
		}
		--top;
		vis[u]=0;
//		printf("out:%d\n",u);
	}
	
	double work(int _k){
		K=_k;
		double ret=0;
		memset(vis,0,sizeof(vis));
		dfs0(1,ret);
		ret*=2.0;
//		return ret;
		
		top=0;
		for (int i=1;i<=c;++i){
			rt=i;
			depth[i]=0;
			dfs1(i,ret);
		}
		return ret;
	}
};


namespace tree0{
	#define N 2505
	struct edge{
		int adj,next;
		edge(){}
		edge(int _adj,int _next):adj(_adj),next(_next){}
	} e[N*2];
	int n,g[N],m;
	void AddEdge(int u,int v){
		e[++m]=edge(v,g[u]);g[u]=m;
		e[++m]=edge(u,g[v]);g[v]=m;
	}
	bool flag[N];
	void clear(){
		memset(g,0,sizeof(g));m=1;
		memset(flag,0,sizeof(flag));
		n=0;
	}
	int fa[N],depth[N];
	int dfn[N],stamp;
	int list[N];
	int vtree_id[N];
	void dfs0(int u){
		dfn[u]=++stamp;
		if (flag[u]) list[++list[0]]=u,vtree_id[u]=++vtree::n;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa[u]) continue;
			fa[v]=u;
			depth[v]=depth[u]+1;
			dfs0(v);
		}
	}
	int qlca(int u,int v){
		while (depth[v]>depth[u]) v=fa[v];
		while (depth[u]>depth[v]) u=fa[u];
		while (u!=v) u=fa[u],v=fa[v];
		return u;
	}
	int stk[N],top;
	void dfs1(int u){
		if (flag[u]){
			if (top) vtree::AddEdge(vtree_id[u],vtree_id[stk[top-1]],depth[u]-depth[stk[top-1]]);
			stk[top++]=u;
		}
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa[u]) continue;
			dfs1(v);
		}
		if (flag[u]) --top;
	}
	void build_vtree(){
		fa[1]=0;
		depth[0]=0;depth[1]=1;
		memset(dfn,0,sizeof(dfn));stamp=0;
		list[0]=0;
		vtree::clear();
		dfs0(1);
		vtree::c=vtree::n;
		for (int i=1;i<list[0];++i){
			int lca=qlca(list[i],list[i+1]);
			if (!flag[lca]) flag[lca]=1,vtree_id[lca]=++vtree::n;
		}
		top=0;
		dfs1(1);
	}
};

class Orienteering{
	int r,c;
	int id[66][66];
	public:
	double expectedLength(vector <string> field, int K){
		r=field.size();
		c=field[0].size();
		tree0::clear();
		memset(id,0,sizeof(id));
		for (int i=0;i<r;++i)for (int j=0;j<c;++j)if (field[i][j]!='#'){
			id[i][j]=++tree0::n;
			if (field[i][j]=='*') tree0::flag[id[i][j]]=1;
			if (i&&id[i-1][j]) tree0::AddEdge(id[i-1][j],id[i][j]);
			if (j&&id[i][j-1]) tree0::AddEdge(id[i][j-1],id[i][j]);
		}
		tree0::build_vtree();
		return vtree::work(K);
	}
};
