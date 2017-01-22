
#include<bits/stdc++.h>
#define FT first
#define SC second
#define PB push_back
#define MP make_pair
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define PER(i, r, l) for(int i = (r); i >= (l); i--)
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define ROF(i, n) for(int i = (n) - 1; i >= 0; i--)
#define VEP(i, x) for(int i = 0; i < x.size(); i++)
#define RUN(i, x) for(__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)
#define DFOR(i, x, y) for(int i = hd[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const int inf = 0x3f3f3f3f;
const int MOD = 1000000007;

template <typename tn>
inline tn read(){
	char ch; tn f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	tn x = ch - '0';
	while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
	return x * f;
}
template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int N = 50 + 5;
int matl[N], matr[N], lnk[N], a[N][N], visl[N], visr[N], labl[N], labr[N], slack[N], q[N];
int col[N], f[N][N][N][N], hd[N], tail, tmp[N][N][N];
struct Edge{ int nxt, to; } e[N * 2];
class DeerInZooDivOne  
{  
        public:  
        // km 二分图最大权匹配 
        void modify(int x){ for(int y; x; x = y) y = matl[lnk[x]], matl[matr[x] = lnk[x]] = x; }
        void solve(int x, int n){
        	int l, r;
        	MEM(visl, 0), MEM(visr, 0);
        	for (visl[q[l = r = 1] = x] = 1; 1;){
        		for(int x = q[l]; l <= r; x = q[++l])
        			REP(y, 1, n) if (!visr[y]){
        				int d = labl[x] + labr[y] - a[x][y];
        				if (!d){
        					lnk[y] = x, visr[y] = 1;
        					if (!matr[y]) { modify(y); return; }
        					if (!visl[matr[y]]) visl[q[++r] = matr[y]] = 1;
						} else if (d < slack[y]) slack[y] = d, lnk[y] = x;
					}
				int d = inf;
				REP(i, 1, n) if (!visr[i]) cmin(d, slack[i]);
				REP(i, 1, n) if (visl[i]) labl[i] -= d;
				REP(i, 1, n) 
					if (visr[i]) labr[i] += d;
					else if (slack[i] < inf) slack[i] -= d;
				REP(i, 1, n) if (!visr[i] && !slack[i]){
					if (!matr[i]) {modify(i); return; }
					visr[i] = 1;
					if (!visl[matr[i]]) visl[q[++r] = matr[i]] = 1;
				}
			}
		}
        int match(int n){
        	MEM(labl, 0), MEM(labr, 0), MEM(matl, 0), MEM(matr, 0);
        	REP(i, 1, n) REP(j, 1, n) cmax(labl[i], a[i][j]);
        	REP(i, 1, n) MEM(slack, 0x3f), MEM(lnk, 0), solve(i, n);
        	int ans = 0;
        	REP(i, 1, n) ans += labl[i] + labr[i];
        	return ans;
		}
		
		
		void add(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
        void color(int x){ col[x] = 1; DFOR(i, x, y) if (!col[y]) color(y); }
        //记忆化搜索，f[x][fx][y][fy]表示当前x号节点和y号节点分别作为fx和fy的儿子的最大匹配值。 
        int dfs(int x, int fx, int y, int fy){
        	if (!f[x][fx][y][fy]){
        		int l = 0, r = 0;
        		MEM(tmp[x], 0);
        		DFOR(i, x, sx) if (sx != fx){
        			++l, r = 0;
        			DFOR(j, y, sy) if (sy != fy)
						++r, tmp[x][l][r] = dfs(sx, x, sy, y);
        		}
        		MEM(a, 0);
        		REP(i, 1, l) REP(j, 1, r) a[i][j] = tmp[x][i][j];
        		f[x][fx][y][fy] = match(max(l, r)) + 1;
			}
			return f[x][fx][y][fy];
		}
        int getmax(vector <int> x, vector <int> y)  
        {  
        	int m = x.size(), n = m + 1, ans = 0;
        	FOR(i, m){// 枚举断开一条边。 
        		MEM(hd, 0), tail = 0;
        		FOR(j, m) if (j != i) add(x[j], y[j]), add(y[j], x[j]);
        		MEM(f, 0), MEM(col, 0);
        		color(0);
        		FOR(i, n) FOR(j, n) if (!col[i] && col[j]) cmax(ans, dfs(i, i, j, j));
			}
			return ans;
        }  

};  

