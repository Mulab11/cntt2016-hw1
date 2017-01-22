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
const int MOD = 555555555;
const int N = 3200 + 5;
int c[N][N];

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  

class XorBoard  
{  
        public:  
        int count(int H, int W, int Rcount, int Ccount, int S)  
        {  
        	int ans = 0;
        	//预处理组合数 
        	REP(i, 0, 3200) REP(j, 0, i) c[i][j] = j == 0 ? 1 : (c[i - 1][j] + c[i - 1][j - 1]) % MOD; 
        	REP(A, 0, H) REP(B, 0, W) //枚举多少个翻转次数是奇数的行，以及翻转次数是奇数的列 
				if ((H - A) * B + A * (W - B) == S && Rcount >= A && Ccount >= B && ((Rcount - A) & 1 ^ 1) && ((Ccount - B) & 1 ^ 1))//判断是否满足1的个数是否合法，以及翻得次数能否合法。 
                    ans = (ans + ((LL)c[H + ((Rcount - A) >> 1) - 1][H - 1] * c[H][A] % MOD) * 
                                 ((LL)c[W + ((Ccount - B) >> 1) - 1][W - 1] * c[W][B] % MOD)) % MOD;//组合数更新答案。 
        	return ans;
		}
};  
