#include <bits/stdc++.h>

using namespace std;
const int N = 60;
typedef long long ll;
struct Edge{
	int end,next;
};

class CentaurCompany{
	public:
		int n,first[N],efn,siz[N];
		ll f[N][N<<2][2],g[N<<2][2],w;
		Edge edge[N<<1];
		double getvalue(vector <int> a, vector <int> b){
			double ans = 0;
			n = a.size()+1;
			w = 1;w <<= n;			
			for (int i = 0;i < n-1;i++)
				 addedge(a[i],b[i]);
			dfs(1,0);
			for (int i = N+1;i <= N + n;i++){
				ans += (double) f[1][i][0]*(i-N)/w;
				ans += (double) f[1][i][1]*(i-N)/w;				
				//cout << f[1][i][0] << ' ' << f[1][i][1] << endl;
			}
//			ans /= w;
			return ans*2;
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
			siz[x] = 1;
			f[x][N-1][1] = 1;
			f[x][N-2][0] = 1;
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (u != y){
					dfs(u,x);
					
					memset(g,0,sizeof(g));
					for (int i = N - siz[u]-2;i <= N + siz[u];i++)
						for (int j = N - siz[x]-2;j <= N + siz[x];j++){
							g[i+j-N+2][0] += f[x][j][0]*f[u][i][0];
							g[i+j-N+2][0] += f[x][j][0]*f[u][i][1];
							g[i+j-N+2][1] += f[x][j][1]*f[u][i][0];
							g[i+j-N  ][1] += f[x][j][1]*f[u][i][1];							
						}
					siz[x] += siz[u];	
					for (int i = N - siz[x]-2;i <= N + siz[x];i++){
						f[x][i][0] = g[i][0];
						f[x][i][1] = g[i][1];
					}
				}
			}
		}
};
