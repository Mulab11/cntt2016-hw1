
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
  
  
class AlternateColors2  
{  
        public:  
        long long countWays(int n, int k)  
        {  
        	LL ans = 0;
        	int tmp;
			//第k个球的操作存在于三元组中 
			if (k % 3 == 1 && (tmp = (k / 3 + 1) * 3) <= n) ans += LL(n - tmp + 1) * (n - tmp + 2) / 2;
			//直接枚举进行了多少组三元组
        	REP(i, 0, (k - 1) / 3){
        		//第k个球所在的操作存在于二元组中
				if ((k - i * 3) % 2 == 1 && (tmp = (i * 3 + ((k - i * 3) / 2 + 1) * 2)) <= n) ans += (n - tmp + 1) * 2;
				//第k个球所在的操作存在于单元组（红色球）中
				ans += (k - 3 * i - 1) / 2 * 2 + 1;
			}
			return ans;
        }  
  
};  

