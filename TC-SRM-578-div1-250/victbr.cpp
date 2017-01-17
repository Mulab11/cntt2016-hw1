#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int xx[4] = {0,1,0,-1};
const int yy[4] = {1,0,-1,0};
const int N = 2600,mod = 1e9+7;

class GooseInZooDivOne{
	public:
		int n,m,ans,dist;
		int x[N],y[N],len,fa[N],siz[N];
		int count(vector <string> field, int dis){
			n = field.size();dist = dis;
			m = field[0].size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					if (field[i][j] == 'v'){
						x[++len] = i;
						y[  len] = j;
					}
			for (int i = 1;i <= len;i++) fa[i] = i;
			bfs();
			for (int i = 1;i <= len;i++){
				fa[i] = getfa(fa[i]);
				siz[fa[i]]++;
			}
			int u = 0,v = 0;
			for (int i = 1;i <= len;i++)
				if (siz[i]>0){
					if (siz[i]&1) u++;else v++;
				}
		//printf("%d %d\n",u,v);
			ans = power(2,max(0,u-1)+v)-1;
			return ans;
		}
		void bfs(){
			static int f[N][N],g[N][N];
			static int u[N],v[N];
			int t = 1,w = 0;
			memset(f,0x3f,sizeof(f));
			memset(g,0,sizeof(g));
			
			for (int i = 1;i <= len;i++){
				u[++w] = x[i];
				v[  w] = y[i];
				f[x[i]][y[i]] = 0;
				g[x[i]][y[i]] = i;
			}
			while (t <= w){
				for (int i = 0;i < 4;i++){
					if (0 <= u[t]+xx[i] && u[t]+xx[i] < n && 0 <= v[t]+yy[i] && v[t]+yy[i] < m){
						if (f[u[t]+xx[i]][v[t]+yy[i]]>f[u[t]][v[t]]+1){
							f[u[t]+xx[i]][v[t]+yy[i]] = f[u[t]][v[t]]+1;
							g[u[t]+xx[i]][v[t]+yy[i]] = g[u[t]][v[t]];
							u[++w] = u[t]+xx[i];
							v[  w] = v[t]+yy[i];
						}
						else if (f[u[t]+xx[i]][v[t]+yy[i]] + f[u[t]][v[t]]+1 <= dist){
							int x = g[u[t]][v[t]],y = g[u[t]+xx[i]][v[t]+yy[i]];
							fa[x] = getfa(fa[x]);
							fa[y] = getfa(fa[y]);
							if (fa[x] != fa[y]) fa[fa[x]] = fa[y];
						}
					}
				}
				t++;
			}
		}
		int getfa(int x){
			if (fa[x] == x) return x;
			fa[x] = getfa(fa[x]);
			return fa[x];
		}
		int power(int x,int y){
			int ans = 1;
			while (y){
				if (y&1) ans = (ll) ans * x % mod;
				x = (ll) x * x % mod;
				y >>= 1;
			}
			return ans;
		}
};

