#include <bits/stdc++.h>

using namespace std;

const int N = 60;

struct Edge{
	int next,end;
};

class Incubator{
	public:
		int n,first[N],efn,used[N],ans;
		bool a[N][N],vist[N];
		Edge edge[N*N];
		int maxMagicalGirls(vector<string> love){
			n = love.size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					if (love[i][j] == 'Y') a[i][j] = 1;
			for (int k = 0;k < n;k++)
				for (int i = 0;i < n;i++)	
					for (int j = 0;j < n;j++)
						a[i][j] = a[i][j] | (a[i][k]&a[k][j]);
			for (int i = 0;i < n;i++)				
				for (int j = 0;j < n;j++)
					if (a[i][j]) addedge(i+1,j+1);
			for (int i = 1;i <= n;i++){
				memset(vist,0,sizeof(vist));
				ans += dfs(i);
			}
			return n-ans;
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;
		}
		bool dfs(int x){
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (!vist[u]){
					vist[u] = 1;
					if (used[u] == 0){used[u] = x;return 1;}
					if (dfs(used[u])){used[u] = x;return 1;}
				}
			}
			return 0;
		}
};
