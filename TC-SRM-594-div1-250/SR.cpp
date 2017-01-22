
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
  
const int N = 50 + 5;
int f[N][N];
class AstronomicalRecords  
{  
        public:  
        int minimalPlanets(vector <int> a, vector <int> b)  
        {  
        	//枚举比例后问题转化为最长公共子序列。
        	int n = a.size(), m = b.size(), ans = inf;
        	FOR(t1, n) FOR(t2, m){
        		MEM(f, 0);
        		REP(i, 0, n) REP(j, 0, m){
					if ((LL)a[i] * b[t2] == (LL)b[j] * a[t1] && i < n && j < m) cmax(f[i + 1][j + 1], f[i][j] + 1);
					if (i < n) cmax(f[i + 1][j], f[i][j]);
					if (j < m) cmax(f[i][j + 1], f[i][j]);
				}
				cmin(ans, n + m - f[n][m]);
			}
			return ans;
        }  
     
};  

