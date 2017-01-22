
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

const int N = (1 << 16) + 5;
LL f[N], g[N];
class StringPath  
{  
        public:  
        int countBoards(int n, int m, string A, string B)  
        {  
        	//考虑状态压缩轮廓线dp，f[i][j][mask]表示到了第i,j个位置，对应列和两个字符串匹配关系的状态为mask的方案数。
			//虽然我用了滚动数组，但我觉得应该不妨碍大家阅读我的程序。 
        	MEM(f, 0), MEM(g, 0);
        	f[3] = 1;
        	FOR(i, n) FOR(j, m){
        		MEM(g, 0);
        		FOR(now, 1 << (m * 2)){
        			int L = j ? now >> (j * 2 - 2) & 3 : 0, R = now >> (j * 2) & 3;
        			int sta = now >> (j * 2 + 2) << (j * 2 + 2) | now & ((1 << (j * 2)) - 1);
        			if (A[i + j] == B[i + j]){
						(g[sta | (L & 3 | R & 3) << (j * 2)] += f[now]) %= MOD;
						(g[sta] += f[now] * 25) %= MOD;
					} else {
        				(g[sta | (L & 1 | R & 1) << (j * 2)] += f[now]) %= MOD;
        				(g[sta | (L & 2 | R & 2) << (j * 2)] += f[now]) %= MOD;
						(g[sta] += f[now] * 24) %= MOD;
					}
				}
        		swap(f, g);	
			}
			LL ans = 0;
			FOR(now, 1 << (m * 2)) if (now >> (m * 2 - 2) == 3) (ans += f[now]) %= MOD;
			return ans;
        }  
 
};  

