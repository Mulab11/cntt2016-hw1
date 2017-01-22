
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
  
const int N = 80 + 5;
int K, Count[3], f[N][N];
struct Matrix{
	int n[N][N]; 
	Matrix(){ MEM(n, 0); }
	void set(){ REP(i, 1, K) n[i][i] = 1; }
};
inline Matrix operator * (const Matrix &a, const Matrix &b){
	Matrix c;
	REP(i, 1, K) REP(j, 1, K) REP(k, 1, K)
		c.n[i][k] = (c.n[i][k] + (LL)a.n[i][j] * b.n[j][k]) % MOD;
	return c;
}
inline Matrix pw(Matrix x, int k){
	Matrix s; s.set();
	for (; k; k >>= 1, x = x * x) if (k & 1) s = s * x;
	return s;
}
class ConversionMachine  
{  
        public:  
        int countAll(string word1, string word2, vector <int> costs, int maxCost)  
        {  
			int n = word1.size(), m = 0;
			
			LL Up = maxCost; //防止爆int
			MEM(Count, 0);
			FOR(i, n){
				int tmp = 0;
				for (int x = word1[i] - 'a', y = word2[i] - 'a'; x != y; x = (x + 1) % 3) ++tmp, Up -= costs[x];
				m += tmp, Count[tmp]++; //预处理转移类型 
			}
			if (Up < 0) return 0;//如果代价不足够完成最低限度的操作，那么返回0 
			m += Up / (costs[0] + costs[1] + costs[2]) * 3; //计算在不超过上限代价，可以进行操作的次数 
			
			//预处理状态 
			K = 0;
			REP(i, 0, n) REP(j, 0, n - i) f[i][j] = ++K;
			
			//预处理转移
			Matrix A;
			REP(i, 0, n) REP(j, 0, n - i){
				if (i) A.n[f[i][j]][f[i - 1][j + 1]] = i;
				if (j) A.n[f[i][j]][f[i][j - 1]] = j;
				if (n - i - j) A.n[f[i][j]][f[i + 1][j]] = n - i - j;
			}
			++K, A.n[f[0][0]][K] = 1, A.n[K][K] = 1;//预处理前缀和转移 
			
			return pw(A, m + 1).n[f[Count[2]][Count[1]]][K];
        }  

};  
