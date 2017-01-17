#include <bits/stdc++.h>

using namespace std;

const int N = 60;
const int u[4] = {0,1,0,-1},v[4] = {1,0,-1,0};


struct Edge{
	int end,next;
};


class GameInDarknessDiv1{
	public:
		bool flag;
		int n,m,b[N][N],len,fa[N*N],up[N*N],down[N*N];
		int disA[N*N],disB[N*N];
		int first[N*N],efn,A,B;
		Edge edge[N*N<<1];
		string check(vector <string> a){
			n = a.size();
			m = a[0].size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					if (a[i][j] != '#'){
						b[i][j] = ++len;
						if (a[i][j] == 'A') A = len;
						if (a[i][j] == 'B') B = len;
					}
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					if (b[i][j] != 0)
					for (int k = 0;k < 4;k++){
						int x = i+u[k],y = j+v[k];
						if (x < 0 || y < 0 || x >= n || y >= m) continue;
						if (b[x][y] != 0) 
							addedge(b[i][j],b[x][y]);
					}
			dfs4(B,0);
			dfs(A,0);
			if (fa[B] == A) return "Alice wins";
			int C = B;
			while (fa[C] != A) C = fa[C];
			dfs2(A,C);
			flag = 0;dfs3(C,A);
			if (flag) return "Bob wins";
			else return "Alice wins";
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;	
		}
		void dfs(int x,int y){
			fa[x] = y;
			disA[x] = disA[y]+1;
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (u != y)dfs(u,x);		
			}
		}
		void dfs4(int x,int y){
			disB[x] = disB[y]+1;
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (u != y)dfs4(u,x);		
			}
		}
		void dfs2(int x,int y){
			up[x] = 0;
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (u != y){
					dfs2(u,x);		
					up[x] = max(up[x],up[u]);
				}
			}
			up[x]++;
		}
		void dfs3(int x,int y){
			up[x] = up[y]+1;
			down[x] = 0;
			int cnt = (up[y] > 2);
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (u != y){
					dfs3(u,x);	
					down[x] = max(down[x],down[u]);
					cnt += (down[u] > 2);
				}
			}
			if (cnt > 2 && disA[x] >= disB[x]+2) flag = 1;//bob必需比alice先到才有用 
			down[x]++;
		}
};
