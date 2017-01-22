
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
  
const int N = 2500 + 5;
int vis[N], g[N][N], now, n, pw[N];
PI a[N];
class GooseInZooDivOne  
{  
        public:  
        //为集合标上号码 
        int dfs(int x){
        	vis[x] = 1, now ^= 1;
        	FOR(y, n) if (g[x][y] && !vis[y]) dfs(y);
		}
        int count(vector <string> field, int dist)  
        {  
            n = 0;
            //建图建边 
            VEP(i, field) VEP(j, field[i]) if (field[i][j] == 'v') a[n++] = MP(i, j);
            FOR(i, n) FOR(j, n) g[i][j] = bool(abs(a[i].FT - a[j].FT) + abs(a[i].SC - a[j].SC) <= dist);
            MEM(vis, 0);
            //预处理出偶数集合和奇数集合 
        	int cnt[2] = {0, 0};
        	FOR(i, n) if (!vis[i]){
				now = 0, dfs(i), ++cnt[now];
			}  
			pw[0] = 1; 
			REP(i, 1, n) pw[i] = pw[i - 1] * 2 % MOD;
			if (cnt[1] == 0) return (pw[cnt[0]] + MOD - 1) % MOD;
			else return (pw[cnt[0] + cnt[1] - 1] + MOD - 1) % MOD;
        }  
        
  
};  

