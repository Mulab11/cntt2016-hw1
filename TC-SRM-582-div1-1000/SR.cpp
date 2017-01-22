
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
const int MOD = 1000000009;

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
  
const int N = 1400 + 5, M = 3000 + 5; 
int inv[N], sum[N], f[N][N], sumc[N][M], a[N];
class ColorfulBuilding  
{  
        public:  
        int happy(const char a){ return a >= 'a' && a <= 'z' ? a - 'a' + 26 : a - 'A'; }
        int count(vector <string> color1, vector <string> color2, int L)  
        {  
        	int n = 0;
        	MEM(a, 0), MEM(sum, 0), MEM(sumc, 0);
        	VEP(i, color1) VEP(j, color1[i]) a[++n] += happy(color1[i][j]) * 52;
        	n = 0;
        	VEP(i, color2) VEP(j, color2[i]) a[++n] += happy(color2[i][j]);
        	
        	inv[0] = inv[1] = 1;
        	REP(i, 2, n) inv[i] = LL(MOD - MOD / i) * inv[MOD % i] % MOD;//预处理逆元 
        	
			sum[0] = 1;
			REP(i, 1, n){
				REP(j, 1, i) f[i][j] = (LL)((LL)sum[j - 1] - sumc[j - 1][a[i]] + sumc[j][a[i]] + MOD) * inv[n - i] % MOD;
				//转移时注意要减去j-1中相同颜色的答案，加上j中相同的答案。 
				REP(j, 1, i) sum[j] = (sum[j] + f[i][j]) % MOD;          //前缀和 
				REP(j, 1, i) sumc[j][a[i]] = (sumc[j][a[i]] + f[i][j]) % MOD;    //相同颜色的前缀和 
			} 
			int ans = f[n][L]; 
			REP(i, 1, n - 1) ans = (LL)ans * i % MOD;
			return ans;
        }  

};  

