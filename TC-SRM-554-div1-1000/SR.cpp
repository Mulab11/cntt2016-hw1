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
#define pos(x, y) ((y) * k + x)

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const int inf = 0x7fffffff;
const int MOD = 1234567891;

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int N = 120 + 5, M = 4747 + 5;
int color[N], neigh[N], n, k, A[N][N], a[N], b[N];
int inv[M], fac[M], invfac[M];
int C, K;

//矩阵乘法 
struct matrix{
	int n[N][N];
	matrix(int k = 0){ MEM(n, 0); if (k == 1) FOR(i, N) n[i][i] = 1; }
}Trans;

inline matrix operator * (const matrix &a, const matrix &b){
	matrix c(0);
	REP(i, 1, n) REP(j, 1, n) REP(k, 1, n)
		c.n[i][k] = (c.n[i][k] + (LL)a.n[i][j] * b.n[j][k]) % MOD;
	return c;	
}
inline matrix pw(matrix a, LL k){
	matrix s(1);
	for(; k; k >>= 1, a = a * a) if (k & 1) s = s * a;
	return s;
}
//预处理状态 
void make(int x, int s){
	if (x > 4){ 
		++k; 
		color[k] = s;
		neigh[k] = (a[1] == a[2]) + (a[2] == a[3]) + (a[3] == a[4]) + (a[4] == a[1]);
		REP(i, 1, 4) A[k][i] = a[i];
		return;
	}
	REP(i, 1, s + 1) a[x] = i, make(x + 1, max(s, i));
}
int calc(int a[]){
	REP(i, 1, k){
		int can = 1;
		REP(j, 1, 4) if (A[i][j] != a[j]) can = 0;
		if (can) return i;
	}
}
int cc(int x, int y){ if (x < 0 || y > x) return 0; else return (LL)fac[x] * invfac[x - y] % MOD; }
//预处理转移 
void dev(int x, int s){
	if (x > 8){
		int tot = 0;
		
		REP(i, 1, 4) a[i + 4];
		
		int vis[5];
		MEM(vis, 0);
		REP(i, 1, 4) if (!vis[i]){
			++tot;
			PER(j, 4, i) if (a[i + 4] == a[j + 4]) vis[j] = 1, b[j] = tot;
		}
		int X = calc(a), Y = calc(b);
		
		int col = 4;
		REP(i, 5, 8) REP(j, 1, i - 1) if (a[i] == a[j]) {--col; break;}
		
		int nei = (a[1] == a[5]) + (a[2] == a[6]) + (a[3] == a[7]) + (a[4] == a[8]) + neigh[Y];
		
		REP(i, 0, K - nei) Trans.n[pos(X, i)][pos(Y, i + nei)] = ((LL)Trans.n[pos(X, i)][pos(Y, i + nei)] + cc(C - (s - col), col)) % MOD;
		
		return;
	}
	REP(i, 1, s + 1) a[x] = i, dev(x + 1, max(s, i));
} 
class TheBrickTowerHardDivOne  
{  
        public:  
        int find(int CC, int KK, long long H)  
        {  
        	C = CC, K = KK, MEM(Trans.n, 0);
			
			//预处理阶乘以及逆元        	
        	inv[1] = fac[0] = invfac[0] = 1;
        	REP(i, 2, C) inv[i] = LL(MOD - MOD / i) * inv[MOD % i] % MOD;
        	REP(i, 1, C) fac[i] = (LL)fac[i - 1] * i % MOD;
        	REP(i, 1, C) invfac[i] = (LL)invfac[i - 1] * inv[i] % MOD;
        	
        	k = 0;
        	make(1, 0);//生成所有状态 
        	dev(1, 0);//生成所有转移
        	
        	matrix Start;
        	REP(i, 1, k) if (neigh[i] <= K) Start.n[1][pos(i, neigh[i])] = cc(C, color[i]);
        	n = (K + 1) * k + 1;
        	REP(i, 1, n) Trans.n[i][n] = 1;
        	
        	return (Start * pw(Trans, H)).n[1][n];
        }  
};  
