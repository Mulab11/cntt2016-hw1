#include <bits/stdc++.h>

using namespace std;

const int N = 60;

struct Edge{
	int end,next;
};

class TPS{
	public:
		int ans,first[N],efn,n,f[N];
		Edge edge[N<<1];
		int minimalBeacons(vector <string> linked){
			n = linked.size();ans = n;//节点从0到n-1 
			if (n == 1) return 0;//只有1个点时答案为0 
			for (int i = 0;i < n;i++)	
				for (int j = i+1;j < n;j++)
					if (linked[i][j] == 'Y')
						addedge(i+1,j+1);
			for (int i = 1;i <= n;i++) {
				memset(f,0,sizeof(f));
				dp(i,0);
				ans = min(ans,f[i]+1);
			}
			return ans;
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;
			edge[++efn].end = x;
			edge[  efn].next = first[y];
			first[y] = efn;
		}
		void dp(int x,int y){//只有叶子节点有用。并且若其他子树都被识别，则剩下的一个叶子节点无需识别 
			bool flag = 0;
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (u != y){
					dp(u,x);
					if (f[u] == 0) flag = 1;
					f[x] += max(1,f[u]);
				}
			}
			f[x] -= flag;
		}
}; 
