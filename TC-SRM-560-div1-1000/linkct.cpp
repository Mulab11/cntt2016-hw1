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
			double ans, ave; string str;
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
					//printf("here\n");
					for(u = 0; u < n; ++ u){
						if(~val[u]) continue;
						for(v = u + 1; v < n; ++ v)
							if(val[v] == -1 && !g[u][v]) break;
						if(v != n) break;
					} if(u != n) continue;
					cur = sum - cur;
					//printf("prep done, %d remain (%d %d)\n", cur, i, j);
					for(u = ave = 0; u < n; ++ u){
						if(~val[u]) continue;
						for(v = tot[u] = 0; v < n; ++ v)
							if((~val[v]) && g[u][v])
								tot[u] += val[v];
						ave += tot[u];
					} ave = (ave + (cnt / 2.0 - 1) * cur) / cnt;
					//printf("ave d. = %.3lf, cur = %d, cnt = %d\n", ave, cur, cnt);
					for(k = 0; k < n; ++ k){
						if(~val[k]) continue;
						fin[k] = cur / 2.0 + tot[k] - ave;
						if(fin[k] < l[k] || fin[k] > r[k]) break;
					} if(k != n) continue;
					//for(k = 0; k < n; ++ k)
					//	printf("%.3lf ", fin[k]);
					ans = max(ans, calc());
					//printf("i = %d j = %d done, res = %.3lf\n", i, j, calc());
					if(!j) break;
				}
			return ans;
		}
}x;

int main(){
	int lb[] = {57,29,50,21,49,29,88,33,84,76,95,55,11}, rb[] = {58,80,68,73,52,84,100,79,93,98,95,69,97}, sum = 845;
	const char *inp[] = {"db+ea+ik+kh+je+","fj+lk+i","d+jb+h","a+gk+mb+ml+lc+mh+cf+fd+","gc+ka+gf+bh+mj+eg+bf+hf+l","b+al+ja+da+i",
"f+g","h+ia+le+ce+gi+d","h+mc+fe+dm+im+kb+bc+","ib+ma+eb+mf+jk+kc+mg+mk+","gb+dl+ek+hj+dg+hi","+ch+ga+ca+fl+ij+fa+jl+dc+dj+fk","+li+jg"};
	vector <string> expr(inp, inp + (sizeof(inp) / sizeof(char *)));
	vector <int> l(lb, lb + sizeof(lb) / sizeof(int)), r(rb, rb + sizeof(rb) / sizeof(int));
	printf("%.9lf\n", x.maxValue(expr, l, r, sum));
}
