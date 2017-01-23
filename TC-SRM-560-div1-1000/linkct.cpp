#include <cstdio>
#include <string>
#include <vector>
const int MAXN = 15;
using namespace std;

class BoundedOptimization{
	public:
		int g[MAXN][MAXN], val[MAXN], n, N, tot[MAXN]; double fin[MAXN];
		inline double calc(){
			double ret = 0.0; int i, j;
			for(i = 0; i < n; ++ i)
				for(j = i + 1; j < n; ++ j)
					if(g[i][j]) ret += fin[i] * fin[j];
			return ret;
		}
		double maxValue(vector <string> expr, vector <int> l, vector <int> r, int sum){
			int i, j, k, u, v, cnt, cur, minv;
			double ans = 0.0, ave; string str;
			n = l.size(), N = (1 << n) - 1;
			for(i = 0; i < int(expr.size()); ++ i) str += expr[i];
			for(i = 0; i < int(str.size()); i += 3){
				u = str[i] - 'a', v = str[i + 1] - 'a';
				g[u][v] = g[v][u] = 1, ans += l[u] * l[v];
			}
			for(i = 0; i <= N; ++ i)
				for(j = i; j >= 0; j = (j ? ((j - 1) & i) : -1)){
					for(cnt = cur = minv = k = 0; k < n; ++ k){
						if(j & (1 << k)) cur += (val[k] = fin[k] = l[k]);
						else if(i & (1 << k)) cur += (val[k] = fin[k] = r[k]);
						else val[k] = -1, minv += l[k], ++ cnt;
					} if(cur + minv > sum) continue;
					if(!cnt){ans = max(ans, calc()); continue;}
					for(u = 0; u < n; ++ u){
						if(~val[u]) continue;
						for(v = u + 1; v < n; ++ v)
							if(val[v] == -1 && !g[u][v]) break;
						if(v != n) break;
					} if(u != n) continue;
					cur = sum - cur;
					for(u = ave = 0; u < n; ++ u){
						if(~val[u]) continue;
						for(v = tot[u] = 0; v < n; ++ v)
							if((~val[v]) && g[u][v])
								tot[u] += val[v];
						ave += tot[u];
					} ave = (ave + (cnt / 2.0 - 1) * cur) / cnt;
					for(k = 0; k < n; ++ k){
						if(~val[k]) continue;
						fin[k] = cur / 2.0 + tot[k] - ave;
						if(fin[k] < l[k] || fin[k] > r[k]) break;
					} if(k != n) continue;
					ans = max(ans, calc());
					if(!j) break;
				}
			return ans;
		}
};
