#include <bits/stdc++.h>

using namespace std;

const int N = 60;

struct Edge{
	int end,next;
};

class HatRack{
	public:	
		int n,first[N],efn,dep[N],flag[N],degree[N];
		int f[N],ans;
		Edge edge[N<<1];
		
		long long countWays(vector <int> knob1, vector <int> knob2){
			n = knob1.size();
			init();
			for (int i = 0;i < n;i++){
				addedge(knob1[i],knob2[i]);
				degree[knob1[i]]++;
				degree[knob2[i]]++;
			}
			n++;
			for (int i = 1;i <= n;i++)
				if (degree[i] == 2) {
					memset(dep,0,sizeof(dep));
					memset(f,0,sizeof(f));
					memset(flag,0,sizeof(flag));
					dfs(i,0);
					ans += f[i];
				//	if (ans > 0) return f[i];
				}
			if (n == 1) return 1;//te pan
			if (n == 2) return 2;//te pan
			return ans;
		}
		void init(){
			memset(first,0,sizeof(first));
			efn = 0;
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;
			edge[++efn].end = x;
			edge[  efn].next = first[y];
			first[y] = efn;
		}
		void dfs(int x,int y){
			int son[3],len;len = 0;
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (u != y) {
					dfs(u,x);
					son[++len] = u;
				}
			}
			if (len == 0) f[x] = 1;
			if (len == 1){
				dep[x] = dep[son[1]]+1;
				flag[x] = 1;
				f[x] = f[son[1]]; 
				if (dep[x] > 1) f[x] = 0;
			}
			if (len == 2){
				dep[x] = max(dep[son[1]],dep[son[2]])+1;
				flag[x] = 1;
				int u = son[1],v = son[2];
				if (abs(dep[u]-dep[v]) > 1) f[x] = 0;
				else{
					if (dep[u] == dep[v] && !flag[u] && !flag[v])
						f[x] = f[u]*f[v]*2,flag[x] = 0;
					else if (dep[u] == dep[v] && !(flag[u]&&flag[v]))
						f[x] = f[u]*f[v];
					else if (dep[u] > dep[v] && !flag[v]) 
						f[x] = f[u]*f[v];
					else if (dep[u] < dep[v] && !flag[u])
						f[x] = f[u]*f[v];
					else f[x] = 0;
				}
				
			}
		}
};
