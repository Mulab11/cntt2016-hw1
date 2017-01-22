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
  
const int N = 120 + 5;
int m[N], l[N], r[N], vis[N];
class NextAndPrev  
{  
        public:  
        int getMinimum(int nxt, int pre, string a, string b)  
        {  
        	MEM(m, -1), MEM(vis, 0);
        	VEP(i, a){
        		if (!~m[a[i] - 'a']) m[a[i] - 'a'] = b[i] - 'a';
        		if (b[i] - 'a' != m[a[i] - 'a']) return -1;//存在一对多映射则不合法 
        		vis[b[i] - 'a'] = 1;
			}
			int tmp = 0;
			FOR(i, 26) tmp += vis[i];
			if (tmp == 26) return a == b ? 0 : -1; //如果目标串中包含26种不同字母，那说明答案不合法。 
			
			int ans = inf;
			FOR(x, 4 * 26){ //枚举分界点进行计算。 
				FOR(i, 26) l[i] = r[i] = i + 2 * 26;
				int bad = 0, mx = 0, tmp = 0;
				REP(i, x, x + 25) if (~m[i % 26])
					if (m[i % 26] < mx) {bad = 1; break;} else mx = m[i % 26];
				if (bad) continue;
				REP(i, x, x + 25) cmin(l[m[i % 26]], i), cmax(r[m[i % 26]], i);
				FOR(i, 26) tmp += nxt * (i + 2 * 26 - l[i]) + pre * (r[i] - i - 2 * 26);
				cmin(ans, tmp);
			}
			return ans == inf ? -1 : ans;
        }  
    
};  

