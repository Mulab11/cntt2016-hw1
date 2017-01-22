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
  
const int N = 50 + 5;
int lnk[N], vis[N], a[N][N], n;

class Incubator  
{  
        public: 
        
		//二分图匹配 
        int dfs(int x){
        	REP(y, 1, n) if (a[x][y] && !vis[y]){
        		vis[y] = 1;
        		if (!lnk[y] || dfs(lnk[y])){ lnk[y] = x; return 1; }
			}
			return 0;
		}
		
        int maxMagicalGirls(vector <string> love)  
        {  
        	int ans = 0;
        	n = love.size();
        	REP(i, 1, n) REP(j, 1, n) a[i][j] = love[i - 1][j - 1] == 'Y';
        	REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) a[i][j] |= (a[i][k] & a[k][j]);//传递闭包 
        	MEM(lnk, 0);
        	REP(i, 1, n){
        		MEM(vis, 0);
				if (dfs(i)) ++ans;
			}
        	return n - ans;
        }   
};  
