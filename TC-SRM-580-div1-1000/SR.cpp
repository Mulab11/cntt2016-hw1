
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
int a[N][N], f[N][N][N][N], n, m, b[N][N];
class WallGameDiv1  
{  
        public:  
        //考虑记忆化搜索，f[i][l][r][x]表示第i层填的墙在l，r的范围内，然后当前位置在x的最小值。 
        int dfs(int i, int l, int r, int x){
			if (l == 1 && r == m) return -inf;
        	if (x <= 0 || x >= m + 1) return inf;
        	if (i == n) return a[i][x];
        	int nl = min(l, x), nr = max(r, x);
        	if (!~f[i][l][r][x]) f[i][l][r][x] = max(dfs(i + 1, m + 1, 0, x) + a[i][x], min(dfs(i, nl, nr, nl - 1) + b[i][x] - b[i][nl - 1], dfs(i, nl, nr, nr + 1) + b[i][nr] - b[i][x - 1]));
			return f[i][l][r][x];
		}
        int play(vector <string> costs)  
        {  
        	MEM(f, -1);
        	n = costs.size(), m = costs[0].size();
			REP(i, 1, n) REP(j, 1, m) a[i][j] = costs[i - 1][j - 1] - '0', b[i][j] = b[i][j - 1] + a[i][j];
			int ans = inf;
			REP(i, 1, m) cmin(ans, dfs(1, m + 1, 0, i));
			return ans;
        }  

};  

