#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef vector <int> vi;
const int MAXN = 55;

class PointyWizardHats{
	public:
		int n, m, g[MAXN][MAXN], match[MAXN], vis[MAXN];
		bool find(int x){ //Hungarian alg.
			for(int i = 1; i <= m; ++ i){
				if(vis[i] || !g[x][i]) continue;
				vis[i] = true;
				if(!match[i] || find(match[i])){
					match[i] = x;
					return true;
				}
			} return false;
		}
		int getNumHats(vi th, vi tr, vi bh, vi br){
			int i, j, ans = 0;
			n = th.size(), m = bh.size();
			for(i = 0; i < n; ++ i)
				for(j = 0; j < m; ++ j) //Check fitness of hats
					if(tr[i] < br[j] && tr[i] * bh[j] < br[j] * th[i])
						g[i + 1][j + 1] = true;
			for(i = 1; i <= n; ++ i){
				memset(vis, false, sizeof(vis));
				if(find(i)) ++ ans;
			}
			return ans;
		}
};
