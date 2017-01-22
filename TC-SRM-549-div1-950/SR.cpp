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

int l, r, n, ans, g[6], b[6];
vector<int> a;

class CosmicBlocks  
{  
        public:  
        //直接暴力搜索 即可。 
        void dfs(int x){
        	int U[6], D[6], f[64];
        	MEM(U, 0), MEM(D, 0), MEM(f, 0);
        	if (x == n){
        		FOR(i, n) FOR(j, n) if (b[i] >> j & 1) ++U[i], ++D[j];
        		FOR(i, n) if (a[i] < U[i] || a[i] < D[i]) return;
        		REP(now, 1, (1 << n) - 1){
        			int cnt = 0, mask = 0, j = -1;
        			FOR(i, n) if (now >> i & 1){
						cnt += a[i] - U[i], mask |= b[i];
						j = j < 0 ? g[i] : j != g[i] ? 0 : j;
					}
					FOR(i, n) if (mask >> i & 1) cnt -= a[i] - D[i];
					if (j && cnt > 0) return;
				}
				f[0] = 1;
				FOR(now, 1 << n){
					int mask = 0;
					FOR(i, n) if (now >> i & 1) mask |= b[i];
					FOR(i, n) if ((now >> i & 1) && (mask >> i & 1 ^ 1))
						f[now] += f[now - (1 << i)];
				}
				if (l <= f[(1 << n) - 1] && r >= f[(1 << n) - 1]) ++ans;
			} else 
			if (g[x]){
				FOR(now, 1 << n){
					int flag = 1;
					FOR(i, n) if (now >> i & 1 && (g[i] != g[x] - 1)) {flag = 0; break;}
					if (flag) b[x] = now, dfs(x + 1); 
				}
			}
			else b[x] = 0, dfs(x + 1);
		}
        void work(int x){
        	if (x == n) dfs(0);
        	else FOR(i, n) g[x] = i, work(x + 1);
		}
        int getNumOrders(vector <int> a, int l, int r)  
        {  
        	::a = a, n = a.size(), ::l = l, ::r = r, ans = 0;
        	work(0);
        	return ans;
        }  
};  

