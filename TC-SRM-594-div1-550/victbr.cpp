#include <bits/stdc++.h>
/*
设白点变空为0，不变为1
空格不变为1，变黑点为0
则S向白连，空向T连，白向空连（相邻的白和空不能为<0,1>） 
*/
using namespace std;

const int u[4] = {0,1,0,-1},v[4] = {1,0,-1,0};
const int inf = 10100,N = 2500+10;
struct Edge{
	int next,end,cap;
};
class FoxAndGo3{
	public:
		int n,m,cnt;
		int first[N],efn,S,T,cur[N],dep[N];
		Edge edge[N*10];
		int maxEmptyCells(vector <string> board){
			n = board.size();
			m = board.size();
			S = n*m+1;T = S+1;efn = 1;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					if (board[i][j] != 'x'){
						cnt++;
						if (board[i][j] == 'o'){
							addedge(S,cal(i,j),1);
							for (int k = 0;k < 4;k++){
								int x = i + u[k],y = j + v[k]; 
								if (x < 0 || y < 0 || x >= n || y >= m) continue;
								if (board[x][y] == '.')
									addedge(cal(i,j),cal(x,y),inf);
							}
						}
						else addedge(cal(i,j),T,1);
					}
			return cnt-dinic();
		}
		int cal(int x,int y){
			return x*m+y+1;
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
			while(bfs()){
				for (int i = 1;i <= T;i++) 
					cur[i] = first[i];
				while (w = dfs(S,inf))
					tot += w;
			}
			return tot;
		}
		bool bfs(){
			static int e[N];
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
			for (int h = first[p];h;h = edge[h].next){
				int u = edge[h].end;
				if (dep[u] == dep[p]+1 && edge[h].cap > 0){
					int x = min(cap,edge[h].cap),y = dfs(u,x);
					cap -= y;tot += y;
					edge[h].cap -= y;
					edge[h^1].cap += y;
					if (cap == 0) return tot;
				}
				cur[p] = h;
			}
			if (tot == 0) dep[p] = -1;
			return tot;
		}
};
