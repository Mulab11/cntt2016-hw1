#include <bits/stdc++.h>

using namespace std;

const int N = 810,M = 5010,inf = 100000000;

struct Edge{
	int end,next,cap;
};

class SurroundingGame {
	public:
		Edge edge[M];
		int S,T,n,m,len,cur[N],first[N],efn,deep[N],sum;
		int maxScore(vector<string> cost, vector<string> benefit) {
			efn = 1;
			n = cost.size();
			m = cost[0].size();
			if (n == 1 && m == 1) 
				return max(0,trans(benefit[0][0])-trans(cost[0][0]));
			S = n*m+1;T = S+1;len = T;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++){
					sum += trans(benefit[i][j]);
					int u = cal(i,j);
					if ((i+j)&1) {
						addedge(S,u,trans(cost[i][j]));
						len++;
						addedge(u,len,trans(benefit[i][j]));
						if (i != 0  ) addedge(len,cal(i-1,j),inf);
						if (j != 0  ) addedge(len,cal(i,j-1),inf);	
						if (i != n-1) addedge(len,cal(i+1,j),inf);
						if (j != m-1) addedge(len,cal(i,j+1),inf);
					}
					else {
						addedge(u,T,trans(cost[i][j]));
						len++;
						addedge(len,u,trans(benefit[i][j]));						
						if (i != 0  ) addedge(cal(i-1,j),len,inf);
						if (j != 0  ) addedge(cal(i,j-1),len,inf);	
						if (i != n-1) addedge(cal(i+1,j),len,inf);
						if (j != m-1) addedge(cal(i,j+1),len,inf);
					}
				}
			return sum-dinic();
		}
		int trans(char c){
			if ('0' <= c && c <= '9') return c-'0';
			if ('a' <= c && c <= 'z') return c-'a'+10;
			if ('A' <= c && c <= 'Z') return c-'A'+36;
			return 0;
		}
		int cal(int x,int y){
			return x*m+y+1;
		}
		int dinic(){
			int tot = 0,w;
			while (bfs()){
				for (int i = 1;i <= len;i++) cur[i] = first[i]; 
				while (w = dfs(S,inf))
					tot += w;
			}
			return tot;
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
		bool bfs(){
			static int e[N];
			memset(deep,-1,sizeof(deep));
			int t = 1,w = 1;e[1] = S;deep[S] = 0;
			while (t <= w){
				int u = e[t];
				for (int h = first[u];h;h = edge[h].next)
					if (edge[h].cap > 0){
						int v = edge[h].end;
						if (deep[v] == -1){
							deep[v] = deep[u]+1;
							e[++w] = v;
						}
					}
				t++;
			}
			return deep[T] != -1;
		}
		int dfs(int p,int cap){
			if (p == T) return cap;
			int tot = 0;
			for (int h = cur[p];h;h = edge[h].next){
				int u = edge[h].end;
				if (edge[h].cap > 0 && deep[u] == deep[p]+1){
					int x = min(cap,edge[h].cap),y = dfs(u,x);
					if (y){
						cap -= y;tot += y;
						edge[h  ].cap -= y;
						edge[h^1].cap += y;
					}	
					if (cap == 0) return tot;
				}
				cur[p] = h;
			}
			if (tot == 0) deep[p] = -1;
			return tot;
		}
};
