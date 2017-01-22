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
  
  
class CheckerExpansion  
{  
        public:  
        vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h)  
        {  
        	vector <string> ans;
        	FOR(i, h){
        		ans.PB("");
				FOR(j, w){
        			char s;
        			LL x = x0 + j, y = y0 + h - i - 1;
        			if ((x ^ y) & 1) s = '.'; // 考虑平移变换后被压缩掉的格子 
					else{
						x = (x - y) / 2; // 将坐标平移变换 
        				if (x & y /* 放置后属于三角形空当部分 */|| x + y >= t /* 回合数未到该棋子放置回合 */) s = '.'; 
						else s = (x ^ y) & 1 ? 'B' : 'A'; /* 最后递归下去到最小的三角形中后判断是谁的棋子 */ 
        			}
        			ans[i] += s;
				}
			}
			return ans;
        }  

};  
