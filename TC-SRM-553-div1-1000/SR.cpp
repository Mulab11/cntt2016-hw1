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
const LL inf = 0x3f3f3f3f3f3f3f3fll;
const int MOD = 1000000007;

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int o = 51, N = 103;

LL f[o + 2][o + 2][N + 2];
void add(int x, int y, int p, int q){ cmin(f[x][y][o + q], (LL)p); }
class YamanoteLine  
{  
        public:  
        long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)  
        {  
			MEM(f, 0x3f);
        	REP(i, 0, n) f[i][i][o] = 0;
        	
			REP(i, 0, n - 1) add(i + 1, i, -1, 0); // d[i] + 1 <= d[i + 1]
			add(0, n, 0, 1), add(n, 0, 0, -1); // d[0] + w == d[n]
			
			VEP(i, s1) add(t1[i], s1[i], -l1[i], int(s1[i] > t1[i]));// d[t] - d[s] >= l | w + d[t] - d[s] >= l
			VEP(i, s2) add(s2[i], t2[i], l2[i], -int(s2[i] > t2[i]));// d[t] - d[s] <= l | w + d[t] - d[s] <= l
			
			//floyd
			REP(k, 0, n) REP(i, 0, n) REP(x, -o, o) if (f[i][k][o + x] < inf) 
					     REP(j, 0, n) REP(y, max(-o, -o - x), min(o, o - x)) if (f[k][j][o + y] < inf)
					     cmin(f[i][j][o + x + y], f[i][k][o + x] + f[k][j][o + y]);
			
			LL l = n, r = inf;
			
			//getans
			REP(i, 0, n) REP(j, -o, o){
				if (j == 0) if (f[i][i][o + j] < 0) return 0; else; else
				if (f[i][i][o + j] < inf)
					if (j > 0) cmax(l, (-f[i][i][o + j] - 1) / j + 1); 
					else cmin(r, f[i][i][o + j] / (-j));
			}
			return (r < l ? 0 : (r == inf ? -1 : r - l + 1));
        }  
};  
 
