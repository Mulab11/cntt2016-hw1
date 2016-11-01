#include <bits/stdc++.h>

using namespace std;
const int N = 60,INF = 0x7fffffff;

class FoxAndCity{
	public:
		struct Edge{
			int end,next,cap;
		}edge[N*N*N];
		int n,a[N][N],b[N],first[N*N],efn,S,T,cur[N*N],dep[N*N];
		int minimalCost(vector <string> linked, vector <int> want){		
			init();
			n = want.size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					a[i+1][j+1] = linked[i][j] == 'Y' ? 1 : 0;
			for (int i = 0;i < n;i++)
				b[i+1] = want[i];
			S = n*n+1;T = S + 1;
			//(i-1)*n+j号节点表示原图中i号节点的第j个点。 
			for (int i = 1;i < n;i++) insert(i,i+1,INF);insert(n,T,INF); 
			for (int i = 1;i < n;i++){
				insert(S,n*i+1,INF);
				for (int j = 1;j < n;j++)
					insert(n*i+j,n*i+j+1,(b[i+1]-j)*(b[i+1]-j));
				//断开i*n+j和i*n+j+1表示第i-1个点的权值取j 
				insert(n*i+n,T,(b[i+1]-n)*(b[i+1]-n));
			}
			for (int i = 1;i <= n;i++)
				for (int j = i+1;j <= n;j++)
					if (a[i][j]){
						for (int k = 1;k < n;k++){
							insert(n*j-n+k+1,n*i-n+k,INF);
							insert(n*i-n+k+1,n*j-n+k,INF);
						}
					}
			return dinic()+b[1]*b[1];//题目保证b[1]=0 
		}
		void init(){
			memset(first,0,sizeof(first));efn = 1;
		}
		void insert(int x,int y,int z){
			edge[++efn].end = y;
			edge[  efn].cap = z;
			edge[  efn].next = first[x];
			first[x] = efn;
			edge[++efn].end = x;
			edge[  efn].cap = 0;
			edge[  efn].next = first[y];
			first[y] = efn;
		}
		int dinic(){//网络流 
			int tot = 0,w;
			while (bfs()){
				for (int i = 1;i <= T;i++) cur[i] = first[i];
				while ( (w = dfs(S,INF)) )
					tot += w;
			}
			return tot;
		}
		bool bfs(){
			static int e[N*N];
			memset(dep,-1,sizeof(dep));
			int t = 1,w = 1;e[1] = S;dep[S] = 0;
			while (t <= w){
				int u = e[t]; 
				for (int h = first[u];h;h = edge[h].next){
					int v = edge[h].end;
					if (dep[v] == -1 && edge[h].cap > 0){
						dep[v] = dep[u]+1;
						e[++w] = v;
					}
				}
				t++;
			}
			return dep[T] != -1;
		}
		int dfs(int p,int cap){
			if (p == T) return cap;
			int sum = 0;
			for (int h = cur[p];h;h = edge[h].next){
				int u = edge[h].end;
				if (edge[h].cap > 0 && dep[u] == dep[p]+1){
					int x = min(edge[h].cap,cap),y = dfs(u,x);
					cap -= y;sum += y;
					edge[h].cap -= y;
					edge[h^1].cap += y;
					cur[p] = h;
					if (cap == 0) return sum;
				} 
			}
			if (sum == 0) dep[p] = -1;
			return sum;
		}
};
