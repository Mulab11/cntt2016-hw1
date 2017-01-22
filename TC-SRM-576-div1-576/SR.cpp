
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
const int inf = 0x7fffffff;
const int MOD = 1000000009;

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
  
const int N = 300 + 5;
int s[N], h[N][N], g[N][N], f[N][N];
class TheExperiment  
{  
        public:  
        int countPlacements(vector <string> S, int m, int l, int A, int B)  
        {  
        	int n = 0;
        	VEP(i, S) VEP(j, S[i]) s[++n] = S[i][j] - 48;
        	REP(i, 1, n) s[i] += s[i - 1];
        	MEM(f, 0), MEM(g, 0), MEM(h, 0);
        	h[0][0] = 1;
        	//考虑dp状态
			//f[i][j]表示前i个水龙头,共放了j个脸盆，最后一个水龙头没有被浪费，最后一个水龙头所在的联通块的所有区间长度都严格小于L方案数。
			//g[i][j]表示前i个水龙头,共放了j个脸盆，最后一个水龙头没有被浪费，最后一个水龙头所在的区间已经出现过一个长度正好为L的区间的方案数。
			//h[i][j]表示前i个水龙头,共放了j个脸盆，最后一个水龙头被浪费的方案数
			//转移就比较简单了，看代码 
        	REP(i, 1, n) REP(j, 0, m){
        		h[i][j] = (g[i - 1][j] + h[i - 1][j]) % MOD;
        		REP(k, 1, min(i, l))
        			if (s[i] - s[i - k] >= A && s[i] - s[i - k] <= B)
        				if (k < l)
        					f[i][j] = ((LL)f[i][j] + f[i - k][j - 1] + h[i - k][j - 1]) % MOD,
        					g[i][j] = (g[i][j] + g[i - k][j - 1]) % MOD;
        				else
        					g[i][j] = ((LL)g[i][j] + f[i - k][j - 1] + g[i - k][j - 1] + h[i - k][j - 1]) % MOD;
			}
			return (g[n][m] + h[n][m]) % MOD;
        }  

};  

