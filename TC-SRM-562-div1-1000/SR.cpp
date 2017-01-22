
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

const int N = 40 + 3;
int hd[N], tail, inv[N], tmp[N][N], fac[N], invfac[N];
int f[N][N], s[N][N], g[N][N][N][N], fa[N], dep[N], n, k;
struct Edge{ int nxt, to; } e[N * 2];
void add(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
void prework(int n){
	fac[0] = inv[1] = invfac[0] = 1;
	REP(i, 2, n) inv[i] = LL(MOD - MOD / i) * inv[MOD % i] % MOD;
	REP(i, 1, n) fac[i] = (LL)fac[i - 1] * i % MOD;
	REP(i, 1, n) invfac[i] = (LL)invfac[i - 1] * inv[i] % MOD;
}
void dfs(int x, int f){
	fa[x] = f, dep[x] = dep[f] + 1;
	DFOR(i, x, y) if (y != f) dfs(y, x);
}
bool judge(int x, int y, int &S, int &T){//判断是否存在一条单的路径 
	vector<int> A, B, All;
	A.PB(x), B.PB(y);
	while (dep[x] > dep[y]) x = fa[x], A.PB(x);
	while (dep[x] < dep[y]) y = fa[y], B.PB(y);
	while (x != y) x = fa[x], y = fa[y], A.PB(x), B.PB(y);
	reverse(B.begin(), B.end());
	REP(i, 1, B.size() - 1) A.PB(B[i]);
	if (A.size() == n - 2 * k + 2){
		REP(i, 1, A.size() - 2) if (e[e[hd[A[i]]].nxt].nxt) return 0;
		S = A[1], T = A[A.size() - 2];
		return 1;
	} else return 0;
}

void work1(int x, int fa){//dp1 
	if (~s[x][fa]) return;
	s[x][fa] = f[x][fa] = 1;
	DFOR(i, x, y) if (y != fa){
		work1(y, x);
		s[x][fa] += s[y][x];
		f[x][fa] = (LL)f[x][fa] * f[y][x] % MOD * invfac[s[y][x]] % MOD;
	}
	f[x][fa] = (LL)f[x][fa] * fac[s[x][fa] - 1] % MOD;
}
int c(int n, int m){ return (LL)fac[n] * invfac[m] % MOD * invfac[n - m] % MOD; }
void work2(int x, int fa){//dp2 
	if (~s[x][fa]) return;
	s[x][fa] = 0, g[x][fa][0][0] = 1;
	DFOR(i, x, y) if (y != fa){
		work2(y, x);
		MEM(tmp, 0);
		s[x][fa] += s[y][x];
		REP(a1, 0, s[x][fa]) REP(a2, 0, s[x][fa] - a1)
			REP(b1, 0, min(a1, s[y][x])) REP(b2, 0, min(a2, s[y][x] - b1))
				tmp[a1][a2] = (tmp[a1][a2] + (LL)g[x][fa][a1 - b1][a2 - b2] * g[y][x][b1][b2] % MOD * c(a1, b1) % MOD * c(a2, b2)) % MOD;
		REP(a1, 0, s[x][fa]) REP(a2, 0, s[x][fa] - a1) g[x][fa][a1][a2]	= tmp[a1][a2];
	}
	s[x][fa]++, g[x][fa][s[x][fa]][0] += g[x][fa][s[x][fa] - 1][0], g[x][fa][0][s[x][fa]] += g[x][fa][0][s[x][fa] - 1];
}
class InducedSubgraphs  
{  
        public:  
        int getCount(vector <int> edge1, vector <int> edge2, int k)  
        {  
        	MEM(hd, 0), tail = 0; 
        	MEM(f, 0), MEM(g, 0), MEM(s, -1);
        	
        	n = edge1.size() + 1, ::k = k;
        	FOR(i, n - 1) add(edge1[i] + 1, edge2[i] + 1), add(edge2[i] + 1, edge1[i] + 1);
        	
			prework(n);
			if (k == 1) return fac[n];
			
			int ans = 0;
			if (2 * k <= n){ //中间一条链两头一坨。 
				dfs(1, 0);
				REP(i, 1, n) REP(j, 1, n){
					int S, T;
					if (judge(i, j, S, T)){
						work1(i, S), work1(j, T);
						if (s[i][S] == k && s[j][T] == k) ans = (ans + (LL)f[i][S] * f[j][T]) % MOD;
					}
				}
			} else { //中间一坨白色点，剩余部分分布着蓝红的子树。
				REP(i, 1, n) work2(i, 0), ans = (ans + g[i][0][n - k][n - k]) % MOD;
				ans = (LL)ans * fac[2 * k - n - 1] % MOD; //公共点任意标号。 
			}
			return ans;
        }  
   
};  

