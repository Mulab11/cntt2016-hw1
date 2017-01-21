// BEGIN CUT HERE

// END CUT HERE
#line 5 "CosmicBlocks.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define INF (1e9)
namespace isap{
	#define N 233
	#define M 100
	struct edge{
		int adj,next,cap;
		edge(){}
		edge(int _adj,int _next,int _cap):adj(_adj),next(_next),cap(_cap){}
	} e[M];
	int n,g[N],m;
	void AddEdge(int u,int v,int c){
//		printf("%d %d %d\n",u,v,c);
		e[++m]=edge(v,g[u],c);g[u]=m;
		e[++m]=edge(u,g[v],0);g[v]=m;
	}
	void clear(){memset(g,0,sizeof(g));m=1;}
	int gap[N],h[N],cur[N],maxflow,flow;
	bool found;
	void aug(int u){
		if (u==n){
			found=1;
			maxflow+=flow;
			return;
		}
		int i,tmp=flow;
		for (i=cur[u];i;i=e[i].next)if (e[i].cap){
			int v=e[i].adj;
			if (h[u]==h[v]+1){
				cur[u]=i;
				flow=min(flow,e[i].cap);
				aug(v);
				if (h[1]==n) return;
				if (found) break;
				flow=tmp;
			}
		}
		if (found){
			e[i].cap-=flow;
			e[i^1].cap+=flow;
		}
		else{
			int minh=n;
			for (int i=cur[u]=g[u];i;i=e[i].next)if (e[i].cap)
				minh=min(minh,h[e[i].adj]+1);
			if (!--gap[h[u]]) h[1]=n;
			++gap[h[u]=minh];
		}
	}
	int doit(){
		memset(h,0,sizeof(h));
		memset(gap,0,sizeof(gap));
		gap[0]=n;
		for (int i=1;i<=n;++i) cur[i]=g[i];
		maxflow=0;
		while (h[1]<n){
			flow=INF;
			found=0;
			aug(1);
		}
		return maxflow;
	}
};

const int maxn=8;

class CosmicBlocks{
	bool _g[maxn][maxn];//_g[u][v]  u->up   v->down
	bool moved[maxn];
	int n,a[maxn];
	
	int bl[maxn];
	int sum[maxn];
	vector<int> blk[maxn];
	
	int res[777];
	int count(int i0){
		if (i0==n) return 1;
		int ret=0;
		for (int i=0;i<n;++i)if (!moved[i]){
			bool valid=1;
			for (int v:blk[bl[i]+1])
				if (_g[v][i]&&!moved[v]){valid=0;break;}
			if (!valid) continue;
			moved[i]=1;
			ret+=count(i0+1);
			moved[i]=0;
		}
		return ret;
	}
	void dfs(int i0,int last,int k){
//		printf("[qaq]%d %d %d\n",i0,last,k);
		if (k>2&&last==-1){
			int _left=sum[k-1];
			isap::clear();isap::n=100;
			for (int u:blk[k-1]){
				int tmp=0;
				for (int v:blk[k-2])
					if (_g[u][v]) ++tmp,isap::AddEdge(u+2,v+2,INF);
				if (a[u]-tmp<0) return;
				isap::AddEdge(1,u+2,a[u]-tmp);
				_left-=tmp;
			}
			for (int v:blk[k-2])
				if (a[v]>=0) isap::AddEdge(v+2,100,a[v]);
				else return;
//			puts("===");
			if (isap::doit()<_left) return;
		}
		if (i0==n){
			if (last!=-1) return;
			memset(moved,0,sizeof(moved));
//			int tmp=count(0);
/*			if (tmp==4){
				for (int i=0;i<n;++i,puts(""))for (int j=0;j<n;++j)
					printf("%d",(int)_g[i][j]);
				puts("");
			}*/
			++res[count(0)];
			return;
		}
		for (int i=last+1;i<n;++i)if (!bl[i]){
			if (sum[k-1]-a[i]<0) continue;
			bl[i]=k;
			sum[k-1]-=a[i];
			sum[k]+=a[i];
			blk[k].push_back(i);
			for (int msk=(1<<(int)blk[k-1].size())-1;msk>=0;--msk){
				for (int j=0;j<blk[k-1].size();++j)
					if (msk&(1<<j)) _g[i][blk[k-1][j]]=1,--a[blk[k-1][j]];
				dfs(i0+1,-1,k+1);
				dfs(i0+1,i,k);
				for (int j=0;j<blk[k-1].size();++j)
					if (msk&(1<<j)) _g[i][blk[k-1][j]]=0,++a[blk[k-1][j]];
			}
			sum[k]-=a[i];
			sum[k-1]+=a[i];
			blk[k].pop_back();
			bl[i]=0;
		}
	}
	public:
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays){
		n=blockTypes.size();
		for (int i=0;i<n;++i) a[i]=blockTypes[i];
		memset(res,0,sizeof(res));
		
		memset(sum,0,sizeof(sum));
		memset(_g,0,sizeof(_g));
		memset(bl,0,sizeof(bl));
		sum[0]=1e9;
		dfs(0,-1,1);
		
		int ret=0;
		for (int i=minWays;i<=maxWays;++i) ret+=res[i];
		return ret;
	}
};
