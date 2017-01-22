
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
int tp[N], hd[N], tail;
struct Edge{ int nxt, to; } e[N * 2];
class TurnOnLamps  
{  
        public:  
        void add(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
        int dfs(int x){
        	int ans = 0;
        	DFOR(i, x, y) ans += dfs(y);
        	if (~tp[x] && ((ans & 1) ^ tp[x])) ++ans;
        	return ans;
		}
        int minimize(vector <int> roads, string SA, string SB)  
        {  
        	//不妨设0号点为根，那么将i到j的路径取反等价于将0到i和0到j的路径取反，因此只要求出最少需要将多少条到根的路径取反，然后除以二上取整就是答案。
			//用f[i]表示i的子树中所有边(包括i连向父亲的边)满足条件时的最少取反路径数，只要先对i的所有儿子的f值求和，然后判断i连向父亲的边是否满足条件，如果不满足再+1即可。
        	MEM(hd, 0), tail = 0;
        	VEP(i, roads){
				add(roads[i], i + 1);
				if (SB[i] == '1') tp[i + 1] = ((SA[i] - '0') ^ 1);
				else tp[i + 1] = -1;
			}
			tp[0] = 0;
			return dfs(0) / 2;
        }  
  
};  

