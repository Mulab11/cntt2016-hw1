#include <bits/stdc++.h>
//S - T |
using namespace std;

const int E = 20100,V = 2600,inf = 1000;

struct Edge{
	int end,next,cap;
};

class BoardPainting{
	public:
		int n,m,ans;
		int dep[V],first[V],cur[V],efn,S,T;
		char a[60][60];
		struct Edge edge[E<<1];
		int minimalSteps(vector <string> target){
			n = target.size();
			m = target[0].size();
			efn = 1;S = n*m+m+1;T = S+1;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					a[i+1][j+1] = target[i][j];
					 
			for (int i = 1;i <= n;i++)
				for (int j = 1;j <= m;j++)
					if (a[i][j] == '#'){
						if (a[i-1][j] == '#') addedge1(cal(i,j),cal(i-1,j),1);
						else addedge2(S,cal(i,j),1);

						if (a[i][j-1] == '#') addedge1(cal(i,j),cal(i,j-1),1);
						else addedge2(cal(i,j),T,1);

						if (a[i+1][j] == '#') ;//addedge(cal(i,j),cal(i+1,j),1);
						else addedge2(S,cal(i,j),1);
						
						if (a[i][j+1] == '#') ;//addedge(cal(i,j),cal(i,j+1),1);
						else addedge2(cal(i,j),T,1);
					}
			ans = dinic()/2;
			return ans;
		}
		void addedge1(int x,int y,int z){
			edge[++efn].end = y;
			edge[  efn].cap = z;
			edge[  efn].next = first[x];	
			first[x] = efn;	
			edge[++efn].end = x;
			edge[  efn].cap = z;
			edge[  efn].next = first[y];	
			first[y] = efn;	
		}
		void addedge2(int x,int y,int z){
			edge[++efn].end = y;
			edge[  efn].cap = z;
			edge[  efn].next = first[x];	
			first[x] = efn;	
			edge[++efn].end = x;
			edge[  efn].cap = 0;
			edge[  efn].next = first[y];	
			first[y] = efn;	
		}
		int cal(int x,int y){
			return x*m+y; 
		}
		int dinic(){
			int tot = 0,w;
			while (bfs()){
				for (int i = 0;i <= T;i++) cur[i] = first[i];
				while ((w=dfs(S,inf))>0){
					tot += w;
				//	cout << w << endl;
				}
			}
			return tot;
		}
		bool bfs(){
			static int e[V];
			memset(dep,-1,sizeof(dep));
			int t = 1,w = 1;e[1] = S;dep[S] = 1;
			while (t <= w){
				int u = e[t];
				for (int h = first[u];h;h = edge[h].next){
					int v = edge[h].end;
					if (edge[h].cap > 0 && dep[v] == -1){
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
			int tot = 0;
			for (int h = cur[p];h;h = edge[h].next){
				int u = edge[h].end;
				if (edge[h].cap > 0 && dep[u] == dep[p]+1){
					int x = min(edge[h].cap,cap),y = dfs(u,x);
					tot += y;cap -= y;
					edge[h  ].cap -= y;
					edge[h^1].cap += y;
				}
				if (cap == 0) return tot;
				cur[p] = h; 
			}
			if (tot == 0) dep[p] = -1;
			return tot;
		}
};
