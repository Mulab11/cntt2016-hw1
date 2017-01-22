
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
  
const int N = 100000 + 5;
int fac[N], inv[N], invfac[N], a[N], b[N];
class WolfPack  
{  
        public:  
        int c(int n, int m){ return (LL)fac[n] * invfac[m] % MOD * invfac[n - m] % MOD; }
        int count(int n, int m){
        	if ((n ^ m) & 1) return 0;
        	if (n < m) return 0;
        	return c(n, (n - m) / 2);
		}
        int calc(int n, int m, int a[]){
        	int ans = 0;
        	REP(x, -300000, 300000){
        		int tmp = 1;
        		FOR(i, n) tmp = (LL)tmp * count(m, abs(a[i] - x)) % MOD;
        		(ans += tmp) %= MOD;
			}
			return ans;
		}
        int calc(vector <int> x, vector <int> y, int m)  
        {  
        	int n = x.size();
        	fac[0] = invfac[0] = inv[1] = 1;
        	REP(i, 2, m) inv[i] = LL(MOD - MOD / i) * inv[MOD % i] % MOD;
        	REP(i, 1, m) fac[i] = (LL)fac[i - 1] * i % MOD;
        	REP(i, 1, m) invfac[i] = (LL)invfac[i - 1] * inv[i] % MOD;
        	
        	//将坐标系旋转45°，然后可以横纵坐标分离，最后将方案相乘。 
        	FOR(i, n) a[i] = x[i] - y[i], b[i] = x[i] + y[i];
        	return (LL)calc(n, m, a) * calc(n, m, b) % MOD;
        }  

  
};  

