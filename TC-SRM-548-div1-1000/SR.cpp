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
  
const int N = 50 + 5, M = N * N;
int c[M][M], f[N][M];
inline int F(int n, int m){ if (n < 0 || m < 0) return 0; return f[n][m]; }
class KingdomAndCities  
{  
        public:  
        int howMany(int N, int M, int K)  
        {  
            REP(i, 0, N * N) REP(j, 0, i) c[i][j] = j ? (c[i - 1][j - 1] + c[i - 1][j]) % MOD : 1;
            
            MEM(f, 0), f[0][0] = 1;
            REP(i, 1, N) REP(j, 0, K){
            	f[i][j] = c[i * (i - 1) / 2][j];
				REP(k, 1, i - 1) REP(l, 0, j) 
					f[i][j] = (f[i][j] - (LL)c[i - 1][k - 1] * f[k][l] % MOD * c[(i - k) * (i - k - 1) / 2][j - l]) % MOD;
			}//通过经典的容斥得到n个点k条边的连通图方案数 

			int ans = 0;
			if (M == 0) 
				ans = f[N][K];
			else	
			if (M == 1){
				ans = (ans + (LL)F(N - 1, K - 1) * (K - 1)) % MOD;//关键点链接的两个点之间没有边的情况 
				ans = (ans + (LL)F(N - 1, K - 2) * (K - 2)) % MOD;//关键点链接的两个点之间有边的情况 
			} else
			if (M == 2){
				
				//两个关键点不链接 
				ans = (ans + (LL)F(N - 2, K - 2) * (K - 2) * (K - 3)) % MOD;//两个关键点链接的两个点之间都没有边。 
				ans = (ans + (LL)F(N - 2, K - 3) * (K - 3) * (K - 4) * 2) % MOD;//一个关键点链接的两个点之间有边，另一个没有边 
				ans = (ans + (LL)F(N - 2, K - 4) * (K - 4) * (K - 4)) % MOD;//两个关键点链接的两个点之间均有边 
				ans = (ans + (LL)F(N - 2, K - 3) * (K - 3)) % MOD;//*特殊情况  两个关键点链接在了同一对点上，而且这一对点之间没有边 
				
				//两个关键点直接连接 
				ans = (ans + (LL)F(N - 2, K - 2) * (K - 2) * 2) % MOD;//链接的两个点之间没有边 
				ans = (ans + (LL)F(N - 2, K - 3) * (K - 3) * 2) % MOD;//链接的两个点之间有边 
				ans = (ans + (LL)F(N - 2, K - 3) * (N - 2)) % MOD;//链接在同一个点上 
			}
			return (ans + MOD) % MOD;
        }  

};  

