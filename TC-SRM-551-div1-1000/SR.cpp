
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
  
const int N = 40 + 5, M = (1 << 20) + 5;
int a[N][N], c[N][N], f[N], S[N], n, m;
PI A[M], B[M];

class SweetFruits  
{  
        public:  
        inline int pw(int x, int k){
        	int s = 1; for (; k; k >>= 1, x = (LL)x * x % MOD) if (k & 1) s = (LL)s * x % MOD; return s;
		}
		
		int det(int n){
			int s = 1;
			FOR(i, n){
				int k = i;
				REP(j, i, n - 1) if (a[j][i] > 0) {k = j; break;}
				if (i != k){ REP(j, i, n - 1) swap(a[i][j], a[k][j]); s = s * (-1); }
				if (!a[i][i]) return 0;
				
				s = (LL)s * a[i][i] % MOD;
				int tmp = pw(a[i][i], MOD - 2);
				REP(k, i + 1, n - 1) PER(j, n - 1, i) a[k][j] = (a[k][j] - (LL)a[k][i] * a[i][j] % MOD * tmp) % MOD;
			}
			return s;
		}//求矩阵行列式 
		
        void getsch(){
        	REP(num, 0, m){
        		FOR(i, n) a[i][i] = 0;
        		FOR(i, n) FOR(j, n) if (i != j){
					int x = i < num ? 1 : (i < m ? 2 : 0);
					int y = j < num ? 1 : (j < m ? 2 : 0);
					if (x + y < 3) a[i][j] = -1, a[i][i]++;
					else a[i][j] = 0;
				}
				f[num] = det(n - 1);
			}
			REP(i, 0, n) REP(j, 0, i) c[i][j] = j == 0 ? 1 : (c[i - 1][j] + c[i - 1][j - 1]) % MOD;//组合数 
			REP(i, 1, m) REP(j, 0, i - 1) f[i] = (f[i] - (LL)c[i][j] * f[j]) % MOD;//容斥 
		} // 预处理x个甜的水果的方案数 
		
        int countTrees(vector <int> sweetness, int maxSweetness)  
        {  
        	sort(sweetness.begin(), sweetness.end());
        	reverse(sweetness.begin(), sweetness.end());
        	n = sweetness.size(), m = 0;
        	RUN(it, sweetness) if (*it > -1) ++m;
        	
        	getsch(); 
			
			//meet in the middle 
			int k = m / 2;
			MEM(A, 0), MEM(B, 0);
			FOR(now, 1 << k) FOR(j, k) if (now >> j & 1) A[now ].FT += sweetness[j], A[now].SC++;
			FOR(now, 1 << (m - k)) REP(j, 0, m - k) if (now >> j & 1) B[now].FT += sweetness[j + k], B[now].SC++;
			sort(A, A + (1 << k)), sort(B, B + (1 << (m - k)));
			
			int i = 0, ans = 0;
			MEM(S, 0);
			//排序后两个单调指针移动，更新答案 
			ROF(j, 1 << (m - k)){
				while (i < (1 << k) && A[i].FT + B[j].FT <= maxSweetness) S[A[i++].SC]++;
				REP(now, 0, k) ans = (ans + (LL)f[B[j].SC + now] * S[now]) % MOD;
			}
			return (ans + MOD) % MOD;
        }  
    
};  

