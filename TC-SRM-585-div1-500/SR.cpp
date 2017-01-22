
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
  
const int N = 36 + 2, M = N * N;
int f[N][M], s[N], c[M][M];
class LISNumber  
{  
        public:  
        int count(vector <int> a, int K)  
        {  
        	int n = a.size();
        	REP(i, 1, n) s[i] = (s[i - 1] + a[i - 1]) % MOD;
        	//预处理组合数 
        	FOR(i, s[n] + 1) REP(j, 0, i) c[i][j] = j == 0 ? 1 : (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        	MEM(f, 0), f[0][0] = 1;
        	//考虑dp f[i][j] 表示考虑了1-i的数，然后最小lisnumber是j的方案数。然后枚举转移，组合数优化转移。 
        	FOR(i, n) REP(j, 0, s[i]) if (f[i][j]) REP(k, 0, min(j, a[i]))
        		f[i + 1][j + a[i] - k] = (f[i + 1][j + a[i] - k] + (LL)c[j][k] * c[s[i] - j + a[i]][a[i] - k] % MOD * f[i][j]) % MOD;
        	return f[n][K];
        }  

};  

