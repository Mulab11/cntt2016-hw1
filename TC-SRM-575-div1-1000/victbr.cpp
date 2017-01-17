#include <bits/stdc++.h>

using namespace std;

const int N = 50;
const int u[2] = {0,1},v[2] = {1,0};

struct Edge{
	int next,end,cap;
};

class TheTilesDivOne{
	public:
		int n,m,a[N+10],S,T,efn;
		Edge edge[(N*N<<3)+10];
		int first[(N*N<<1)+10],cur[(N*N<<1)+10],dep[(N*N<<1)+10];
		int find(vector <string> board){
			n = board.size();
			m = board[0].size();
			S = n*m<<1;T = S+1;efn = 1;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					if (board[i][j] != 'X'){
						if (i + j & 1){
							if (i&1) addedge(S,cal(i,j),1);
							else addedge(cal(i,j),T,1);
						}
						else addedge(cal(i,j),cal(i,j)+n*m,1);
						
						for (int k = 0;k < 2;k++){
							int x = i + u[k],y = j + v[k];
							if (x < 0 || y < 0 || x >= n || y >= m) continue;
							if (board[x][y] == 'X') continue;
							if (i + j & 1){
								if (i&1) addedge(cal(i,j),cal(x,y),1);
								else addedge(cal(x,y)+n*m,cal(i,j),1);
							}
							else{
								if (x&1) addedge(cal(x,y),cal(i,j),1);
								else addedge(cal(i,j)+n*m,cal(x,y),1);
							}
						}
					}
			return dinic();
		}
		int cal(int x,int y){
			return x*m+y;
		}
		void addedge(int x,int y,int z){
			edge[++efn].end = y;
			edge[  efn].cap = z;
			edge[  efn].next = first[x];
			first[x] = efn;
			edge[++efn].end = x;
			edge[  efn].cap = 0;
			edge[  efn].next = first[y];
			first[y] = efn;			
		}
		int dinic(){
			int tot = 0,w;
			while (bfs()){
				for (int i = 0;i <= T;i++) cur[i] = first[i];//因为点的编号是从0开始的 
				while (w = dfs(S,2500)){
					tot += w;
				}
			}
			return tot;
		}
		bool bfs(){
			static int e[(N*N<<1)+10];
			int t = 1,w = 1;
			memset(dep,-1,sizeof(dep));
			dep[S] = 1;e[1] = S;
			while (t <= w){
				int u = e[t];
				for (int h = first[u];h;h = edge[h].next){
					int v = edge[h].end;
					if (edge[h].cap > 0 && dep[v] == -1){
						dep[v] = dep[u] + 1;
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
					int x = min(cap,edge[h].cap),y = dfs(u,x);
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
}A;

