
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

const int N = 360 + 5;
struct Matrix{ 
	int n[N]; 
	Matrix(int x = 0){ MEM(n, 0); if (x == 1) n[0] = 1; }
};
int K;
inline Matrix operator * (const Matrix &a, const Matrix &b){
	Matrix c;
	FOR(i, K) FOR(j, K) c.n[(i + j) % K] = (c.n[(i + j) % K] + (LL)a.n[i] * b.n[j]) % MOD;
	return c;
}
inline Matrix pw(Matrix a, LL k){
	Matrix s(1);
	for(; k; k >>= 1, a = a * a) if (k & 1) s = s * a;
	return s;
}
class PenguinEmperor  
{  
        public:  
        int countJourneys(int n, long long m)  
        {  
        	K = n;
        	Matrix A(1), B, C;
        	//我们可以把跨1步到n步之间预处理，压成一个转移，然后用快速幂加速运算。 
        	FOR(i, n){
        		if (i == (m % n)) C = A;
				MEM(B.n, 0);
				FOR(j, n){
					(B.n[(j - i - 1 + n) % n] += A.n[j]) %= MOD;
					if ((j - i - 1 + n) % n != (j + i + 1) % n) (B.n[(j + i + 1) % n] += A.n[j]) %= MOD;
				}
				A = B;
			}
			return (pw(A, m / n) * C).n[0] % MOD;
        }  
   
};  

