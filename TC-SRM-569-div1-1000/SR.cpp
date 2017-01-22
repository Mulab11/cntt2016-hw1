
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
const int P = 1000000009;
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
  
const int N = 15 + 5;
struct Matrix{ 
	int n[N][N]; 
	Matrix(int x = 0){ MEM(n, 0); if (x == 1) FOR(i, N) n[i][i] = 1; }
};
int n, MOD;
//矩阵乘法 
inline Matrix operator * (const Matrix &a, const Matrix &b){
	Matrix c;
	REP(i, 0, n) REP(j, 0, n) REP(k, 0, n)
		c.n[i][k] = (c.n[i][k] + (LL)a.n[i][j] * b.n[j][k]) % MOD;
	return c;
}
inline Matrix power(Matrix a, int k){
	Matrix s(1);
	for(; k; k >>= 1, a = a * a) if (k & 1) s = s * a;
	return s;
}
inline int pw(int a, int k, int MOD){
	int s = 1;
	for(; k; k >>= 1, a = (LL)a * a % MOD) if (k & 1) s = (LL)s * a % MOD;
	return s;
}
class MegaFactorial  
{  
        public:  
        int calc(int k, int x, int p){
        	MOD = p;
   			if (p == 1) return 0;   
			Matrix S(1), A;
			A.n[0][0] = 1;
   			REP(i, 1, n) REP(j, i, n) A.n[i][j] = 1;
   			while (k){
   				S = power(A, k % x) * S;
   				A = power(A, x);
   				REP(i, 1, n) A.n[0][i] = (A.n[0][i] + 1) % MOD;//常数项+1 
   				k /= x;
			}
			return S.n[0][n];
		}
        int work(int k, int x, int p){
        	// 求[c/x] mod p 
        	return LL((LL)calc(k, x, P) - calc(k, x, p) + P) * pw(p, P - 2, P) % P;
		}
        int countTrailingZeros(int N, int K, int B)  
        {  
        	n = K;
        	REP(i, 2, B){
        		int t = 0;
        		while (!(B % i)) B /= i, ++t;
        		if (B == 1) return work(N, i, t);
        	}
        }  
        

};  

