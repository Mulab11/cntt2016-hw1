
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

const int N = 18 + 5, M = (1 << 18) + 5;
LL f[M][N];

  
class PolygonTraversal  
{  
        public:  
        bool pick(int now, int i, int j, int n){
        	if (i > j) swap(i, j);
        	int flag = 0;
        	REP(tmp, i + 1, j - 1) if (now >> tmp & 1) flag = 1;
        	if (!flag) return 0;
        	flag = 0;
        	REP(tmp, 0, i - 1) if (now >> tmp & 1) flag = 1;
        	REP(tmp, j + 1, n - 1) if (now >> tmp & 1) flag = 1;
        	if (!flag) return 0;
        	return 1;
		}
        long long count(int n, vector <int> p)  
        {  
        	MEM(f, 0);
        	int start = 0, first = p[0] - 1, last = p[p.size() - 1] - 1;
        	VEP(i, p) start |= 1 << (p[i] - 1);
        	//考虑状态压缩dp，状态f[now][i]表示状态为now（01串代表是否取过），当前末尾节点是i的方案有多少种。 
        	f[start][last] = 1;
			FOR(now, (1 << n) - 1) if ((now & start) == start)
				FOR(i, n) if ((now >> i & 1) && f[now][i])
					FOR(j, n) if ((now >> j & 1 ^ 1) && pick(now, i, j, n))
						f[now | 1 << j][j] += f[now][i];
			LL ans = 0;
			FOR(i, n) if ((i + 1) % n != first && (first + 1) % n != i)
				ans += f[(1 << n) - 1][i];
			return ans;	
        }  
    
};  

