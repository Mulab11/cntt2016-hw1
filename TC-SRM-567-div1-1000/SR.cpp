
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

const int N = 50 + 5;
int n, m, can[N][N], h[N];
map<string, int> G[N];
class Mountains  
{  
        public:  
        int dfs(int x, string s){
        	if (x == 0) return 1;
        	if (G[x].find(s) != G[x].end()) return G[x][s];
        	int ans = 0;
        	REP(i, 1, m){
        		int flag = 1;
				REP(j, 1, m)
        			if (can[x][j] ^ (h[x] - abs(j - i) > (int)s[j - 1])){
	        			flag = 0; break;
					}
				if (flag){
					string nxt = s;
					REP(j, 1, m) cmax(nxt[j - 1], char(max(h[x] - abs(j - i), 0)));
					(ans += dfs(x - 1, nxt)) %= MOD;
				}	
			}
        	return G[x][s] = ans;
		}
        int countPlacements(vector <int> heights, vector <string> vis)  
        {  
        	//直接记忆化搜索，复杂度有保证。 
        	n = heights.size(), m = vis[0].size();
        	REP(i, 1, n) h[i] = heights[i - 1];
        	REP(i, 1, n) G[i].clear();
        	REP(i, 1, n) REP(j, 1, m) can[i][j] = vis[i - 1][j - 1] == 'X';
			string s;
			REP(i, 1, m) s.PB(char(0));
			return dfs(n, s);
        }
 
};  

