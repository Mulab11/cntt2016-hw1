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
  
vector<int> pos[26];
class ColorfulChocolates  
{  
        public:  
        int maximumSpread(string chocolates, int maxSwaps)  
        {  
        	int ans = 1;
        	FOR(ch, 26) pos[ch].clear();
        	VEP(i, chocolates) pos[chocolates[i] - 'A'].PB(i);
        	FOR(ch, 26){ //枚举成为最优解的字母种类 
        		int n = pos[ch].size();
        		REP(i, 0, n - 1) REP(j, i, n - 1){ //枚举成为最优解的一连串的原始坐标 
        			int k = i + j >> 1, tot = 0; //最少步数是围绕中位数靠近，所以计算中位数。
					REP(l, i, k) tot += pos[ch][k] - pos[ch][l] - (k - l);
					REP(l, k + 1, j) tot += pos[ch][l] - pos[ch][k] - (l - k);
					if (tot <= maxSwaps) cmax(ans, j - i + 1);//如果交换次数合法，则更新答案。 
        		} 
			}
			return ans;
        }  

};  
