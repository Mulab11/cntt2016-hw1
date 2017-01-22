
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
  
const int N = 50 + 1;
LL f[N][N][N * N];
class LittleElephantAndPermutationDiv1  
{  
        public:  
        int getNumber(int n, int K)  
        {  
        	//考虑dp 我们可以设计状态f[i][j][k]表示已经在b中填充了数1到i，填在下标为i+1到n的数有j个，满足max(a[p],b[p])<=i的max(a[p],b[p])的和为k，这样的的填充方法数。
        	//于是可以分类：
			//将数i填在下标为i处，则k+=i，j不变.
			//将数i填在下标小于i处，下标为i处填入了小于i的数，则k+=2 * i， j--.
			//将数i填在下标小于i处，下标为i处填入了大于i的数，则k+=i，j不变.
			//将数i填在下标大于i处，下标为i处填入了大于i的数，则k不变，j++.
			//将数i填在下标大于i处，下标为i处填入了小于i的数，则k+=i，j不变.
        	MEM(f, 0);
        	f[0][0][0] = 1;
        	FOR(i, n) REP(j, 0, i) REP(k, 0, i * (i + 1)) if (f[i][j][k]){
        		if (j) 
				(f[i + 1][j - 1][k + 2 * (i + 1)] += (LL)f[i][j][k] * j % MOD * j) %= MOD;
        		(f[i + 1][j][k + i + 1] += (LL)f[i][j][k] * j) %= MOD;
        		(f[i + 1][j + 1][k] += f[i][j][k]) %= MOD;
        		(f[i + 1][j][k + i + 1] += (LL)f[i][j][k] * j) %= MOD;
        		(f[i + 1][j][k + i + 1] += f[i][j][k]) %= MOD;
			}
			LL ans = 0;
			REP(k, 0, n * (n + 1)) if (k >= K) (ans += f[n][0][k]) %= MOD;
			REP(i, 1, n) (ans *= i) %= MOD;
			return ans;
        }  
};  

