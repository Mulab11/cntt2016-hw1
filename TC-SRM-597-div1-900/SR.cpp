
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
  
const int N = 2000000 + 5;
int fac[N], invfac[N], inv[N], pw2[N];

void prework(int n){
	inv[1] = fac[0] = invfac[0] = pw2[0] = 1;
	REP(i, 2, n) inv[i] = LL(MOD - MOD / i) * inv[MOD % i] % MOD;
	REP(i, 1, n) fac[i] = (LL)fac[i - 1] * i % MOD;
	REP(i, 1, n) invfac[i] = (LL)invfac[i - 1] * inv[i] % MOD;
	REP(i, 1, n) pw2[i] = (LL)pw2[i - 1] * 2 % MOD;
}
int work(int n, int R, int G){
	if (n < 0) return 0;
	int ans = 0;
	REP(x0, 0, n){
		int x1, x2;
		if ((n - x0 + R - G) & 1) continue; else x1 = (n - x0 + R - G) / 2;
		if ((n - x0 + G - R) & 1) continue; else x2 = (n - x0 + G - R) / 2;
		if (x1 < 0 || x2 < 0) continue;
		
		int now = R - x0 - x1; 
		if (now < 0) continue;
		ans = (ans + (LL)fac[n] * invfac[x0] % MOD * invfac[x1] % MOD * invfac[x2] % MOD * fac[now + n - 1] % MOD * invfac[n - 1] % MOD * invfac[now] % MOD * pw2[x0]) % MOD;
	}
	return ans;
}
class LittleElephantAndBoard  
{  
        public:  
        int getNumber(int M, int R, int G, int B)  
        {  
        	//由于相邻两个不同的原则，而且四个块中每个颜色至少出现一次的原则，我们可以将竖排中两个块看成整体。
			//发现相邻两个竖块本质不同。
			//那么我们可以通过考虑分割的情况去枚举计数。 
			prework(M * 2);
        	R = M - R, G = M - G, B = M - B;
        	return ((LL)work(B - 1, R, G) + work(B, R, G) * 2 + work(B + 1, R, G)) * 2 % MOD;
        }  
  
};  

