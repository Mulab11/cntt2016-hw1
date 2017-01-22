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

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int N = 50 + 5, M = 1024 + 5;;
int v[N], vis[N][M], ans, n, g[N][N];
class XorTravelingSalesman  
{  
        public:  
         
        void dfs(int x, int s){//通过深度优先遍历遍历所有状态。 
        	if (vis[x][s]) return;
        	cmax(ans, s), vis[x][s] = 1;
        	REP(y, 1, n) if (g[x][y]) dfs(y, s ^ v[y]);
		}
        int maxProfit(vector <int> cityValues, vector <string> roads)  
        {  
        	n = cityValues.size(), ans = 0;
        	MEM(vis, 0);
        	REP(i, 1, n) v[i] = cityValues[i - 1];
        	REP(i, 1, n) REP(j, 1, n) g[i][j] = (roads[i - 1][j - 1] == 'Y');
        	dfs(1, v[1]);
        	return ans;
        }  
};  
