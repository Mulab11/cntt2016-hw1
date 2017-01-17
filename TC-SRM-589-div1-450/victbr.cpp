#include <bits/stdc++.h>

using namespace std;

const int N = 60;
struct Edge{
	int end,next;
};
/*
因为节点是从0开始的，所以不能以0为边界。
二分图最大独立集。 
*/
class GearsDiv1{
	public:
		bool vist[N];
		int cnt,n,ans,first[N],efn,used[N];
		Edge edge[N*N<<1];
		int getmin(string color,vector<string>graph){
			n = color.size();ans = n;
			memset(first,0,sizeof(first));efn = 0;cnt = 0;
			memset(used,-1,sizeof(used));
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					if (color[i] == 'R' && color[j] == 'B' && graph[i][j] == 'Y')
						addedge(i,j);
			
			for (int i = 0;i < n;i++) 
				if (color[i] == 'R'){
					memset(vist,0,sizeof(vist));
					cnt += dfs(i);
				}
			ans = min(ans,cnt);
			
			memset(first,0,sizeof(first));efn = 0;cnt = 0;
			memset(used,-1,sizeof(used));
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					if (color[i] == 'R' && color[j] == 'G' && graph[i][j] == 'Y')
						addedge(i,j);
			
			for (int i = 0;i < n;i++) 
				if (color[i] == 'R'){
					memset(vist,0,sizeof(vist));
					cnt += dfs(i);
				}
			ans = min(ans,cnt);

			memset(first,0,sizeof(first));efn = 0;cnt = 0;
			memset(used,-1,sizeof(used));
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					if (color[i] == 'G' && color[j] == 'B' && graph[i][j] == 'Y')
						addedge(i,j);
			
			for (int i = 0;i < n;i++) 
				if (color[i] == 'G'){
					memset(vist,0,sizeof(vist));
					cnt += dfs(i);
				}
			ans = min(ans,cnt);
					
			return ans;
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;
		}
		bool dfs(int p){
			for (int h = first[p];h;h = edge[h].next){
				int u = edge[h].end;
				if (!vist[u]){
					vist[u] = 1;
					if (used[u] == -1) {used[u] = p;return 1;}
					if (dfs(used[u])){
						used[u] = p;
						return 1;
					}
				}
			}
			return 0;
		}
}; 
