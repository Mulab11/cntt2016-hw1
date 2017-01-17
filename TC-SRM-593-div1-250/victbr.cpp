#include <bits/stdc++.h>

using namespace std;

const int u[6] = {0,1,0,-1,1,-1},v[6] = {1,0,-1,0,-1,1};
const int N = 60;

struct Edge{
	int end,next;
};

class HexagonalBoard{
	public:
		int n,m,a[N*N];//点数是N*N的 
		int first[N*N],efn;
		bool flag1,flag2,flag3;
		Edge edge[N*N<<3];//边数是N*N*6的 
		int minColors(vector <string> board){
			n = board.size();
			m = board[0].size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					if (board[i][j] == 'X'){
						flag3 = 1;
						for (int k = 0;k < 6;k++){
							int x = i + u[k],y = j + v[k];
							if (x < 0 || y < 0 || x >= n || y >= m) 
								continue;
							if (board[x][y] == 'X')
								addedge(i*m+j,x*m+y);
						}
					}
			for (int i = 0;i < n*m;i++)
				if (a[i] == 0){
					a[i] = 1;
					dfs(i);
				}
			if (!flag3) return 0;
			if (!flag2) return 1;
			if (!flag1) return 2;
			return 3;
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;
		}
		void dfs(int x){
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (a[u] == 0){
					a[u] = a[x]%2+1;
					flag2 = 1;
					dfs(u);
				}
				else if (a[u]+a[x] != 3) flag1 = 1;
			}
		}
		
};
