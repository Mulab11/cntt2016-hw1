
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
typedef pair<double, double> PI;
const double pi = acos(-1);
const int inf = 0x7fffffff;
const int MOD = 100007;

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

const int N = 233 + 5;
LL s[N][N], cl[N][N];
int h[N][N][2], f[N][N], c[N], v[N][N], g[N][N];
PI a[N], b[N];

inline PI operator - (const PI &a, const PI &b){ return MP(a.FT - b.FT, a.SC - b.SC); }
inline double operator * (const PI &a, const PI &b){ return a.FT * b.SC - a.SC * b.FT; }
class FencingPenguins  
{  
        public:  
        int countWays(int n, int r, vector <int> x, vector <int> y, string color)  
        {  
        	//核心数组有以下几个
			//f[i][j] 记录 表示第i个点到第j个点的弧内部全部符合要求的方案数
			//g[i][j] 记录 表示第i个点到第j个点的弧内部全部符合要求，而且最外部是闭壳的方案 
			//h[i][j][0] 记录 表示第i个点到第j个点的弧内部符合要求，而且最外部是开壳，开壳中有企鹅的方案 
			//h[i][j][1] 记录 表示第i个点到第j个点的弧内部符合要求，而且最外部是开壳，开壳中无企鹅的方案 
			
        	MEM(s, 0), MEM(cl, 0), MEM(h, 0), MEM(f, 0), MEM(v, 0), MEM(c, 0), MEM(g, 0);
        	
        	int m = x.size();
        	FOR(i, n) a[i] = MP((double)r * cos(2 * pi / n * i), (double)r * sin(2 * pi / n * i));
        	FOR(i, m) b[i] = MP((double)x[i], (double)y[i]);
    		FOR(i, m) c[i] = color[i] <= 'Z' ? color[i] - 'A' : color[i] - 'a' + 26;
    		FOR(i, n) FOR(j, n) FOR(k, m)
    			if ((a[j] - a[i]) * (b[k] - a[i]) >= 0) s[i][j] |= 1ll << k, cl[i][j] |= 1ll << c[k];
    		FOR(i, n) FOR(j, n) v[i][j] = !(cl[i][j] & cl[j][i]);
    		
    		REP(i, 1, n - 1) if (s[i][i - 1]) return 0;
    		if (s[0][n - 1]) return 0;
    		
    		FOR(i, n) h[i][i][1] = 1, f[i][i] = 1, f[i][i - 1] = 1;
    		REP(del, 1, n - 1) FOR(i, n - del){
    			int j = i + del;
    			FOR(tp, 2) REP(k, i + 1, j){
    				int nxt = tp || bool(s[i][k] & s[k][j] & s[j][i]); 
    				if (!(s[k][i] & s[i + 1][k - 1])) h[i][j][tp] = (h[i][j][tp] + (LL)f[i + 1][k - 1] * h[k][j][nxt]) % MOD;
				}
				if (!(s[i][j - 1] & s[j][i])) f[i][j] = f[i][j - 1];
				
				g[i][j] = v[i][j] * h[i][j][0];
				REP(k, i + 1, j - 1) if (!(s[i][k - 1] & s[k][j] & s[j][i])) f[i][j] = (f[i][j] + (LL)f[i][k - 1] * g[k][j]) % MOD;
				(f[i][j] += g[i][j]) %= MOD;
			}
			return f[0][n - 1];
        }  

};  

