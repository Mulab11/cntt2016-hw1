#include <bits/stdc++.h>

using namespace std;

const int N = 80,bit = 8;

struct Edge{
	int end,next;
};

struct Node{
	int son[2],tag;
	bool full;
};

class CirclesGame{
	public:
		int sg[N],len,n,fa[N],first[N],efn,root[N],xx[N];
		Edge edge[N];
		Node nod[N*N];
		string whoCanWin(vector <int> x, vector <int> y, vector <int> r){
			n = x.size();
			int tot = 0;
			//建树 
			for (int i = 0;i < n;i++) xx[i] = 20000;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					if (i != j){
						int u = x[i]-x[j],v = y[i]-y[j];
						if (u*u+v*v < r[i]*r[i] && r[i] < xx[j] && r[j] < r[i]) {
							fa[j+1] = i+1;  
							xx[j] = r[i];
						}
					}
			for (int i = 1;i <= n;i++) if (fa[i]) addedge(fa[i],i);
			for (int i = 1;i <= n;i++)
				if (fa[i] == 0){
					dfs(i);
					tot ^= sg[i];
				}
			return tot ? "Alice":"Bob";
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;
		}
		void dfs(int p){
			root[p] = ++len;
			insert(root[p],0,bit);
			int tot = 0;
			for (int h = first[p];h;h = edge[h].next){
				int u = edge[h].end;
				dfs(u);
				tot ^= sg[u];
			}
			for (int h = first[p];h;h = edge[h].next){
				int u = edge[h].end;
				nod[root[u]].tag ^= tot^sg[u];
				root[p] = merge(root[p],root[u],bit);
			}
			sg[p] = find(root[p],bit);
			insert(root[p],sg[p],bit);
		}
		int merge(int x,int y,int d){
			if (x*y == 0) return x+y;
			if (d < 0) return x;//本题中此时x与y必然等价		
			pushdown(x,d);
			pushdown(y,d);	
			nod[x].son[0] = merge(nod[x].son[0],nod[y].son[0],d-1);
			nod[x].son[1] = merge(nod[x].son[1],nod[y].son[1],d-1);
			update(x);
			return x;
		}
		void pushdown(int x,int d){
			if (nod[x].tag & (1<<d)) swap(nod[x].son[0],nod[x].son[1]);
			int u = nod[x].son[0],v = nod[x].son[1];
			nod[u].tag ^= nod[x].tag;
			nod[v].tag ^= nod[x].tag;			
			nod[x].tag  = 0;
		}
		void update(int x){
			nod[x].full = nod[nod[x].son[0]].full & nod[nod[x].son[1]].full;
		}
		int find(int x,int d){
			if (x == 0) return 0;
			if (d <= -1) return 0; 
			pushdown(x,d);
			int ans;
			if (nod[nod[x].son[0]].full) ans = find(nod[x].son[1],d-1)+(1<<d);
			else ans = find(nod[x].son[0],d-1);
			update(x);
			return ans;
		}
		void insert(int x,int y,int d){
			if (d <= -1){nod[x].full = 1;return;}
			pushdown(x,d);
			if (y & (1<<d)) {
				if (nod[x].son[1] == 0) nod[x].son[1] = ++len;
				insert(nod[x].son[1],y,d-1);
			}
			else {
				if (nod[x].son[0] == 0) nod[x].son[0] = ++len;
				insert(nod[x].son[0],y,d-1);
			}
			update(x);
		}
		
}; 
