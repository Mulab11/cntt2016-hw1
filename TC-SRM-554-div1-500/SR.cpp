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
  
const int N = 10000 + 5;
int vis[N], ans[N];

class TheBrickTowerMediumDivOne  
{  
        public:  
        vector <int> find(vector <int> heights)  
        {  
        	//不难看出应该是个谷峰函数
        	MEM(vis, 0);
        	int now = 0;
			ans[0] = 0, vis[0] = 1;
			//递减峰 
			while (1){
				int tmp = inf;
				VEP(i, heights) if (!vis[i] && heights[i] <= heights[ans[now]] && i < tmp) tmp = i;
				if (tmp == inf) break;
				vis[ans[++now] = tmp] = 1;
			}
			//递增峰 
			while (1){
				int tmp = inf;
				VEP(i, heights) if (!vis[i] && (tmp == inf || heights[i] < heights[tmp] || heights[i] == heights[tmp] && i < tmp)) tmp = i;
				if (tmp == inf) break;
				vis[ans[++now] = tmp] = 1;
			}
			vector<int> final;
			REP(i, 0, now) final.PB(ans[i]);
			return final;
        }  
        
};  

