#include <bits/stdc++.h>

#define MODU 1000000009
using namespace std;

int b, cntb ;

typedef unsigned long long ULL ; 


ULL MOD;

const int MAXN = 20;
class Matrix {
		public:
				ULL a[MAXN][MAXN];
				static int n ;
				Matrix() {
						memset(a, 0, sizeof(a));
				}
				Matrix(int) {
						memset(a, 0, sizeof(a));
						for(int i = 0; i < n; i++)
								a[i][i] = 1;
				}
				Matrix operator *(const Matrix &ano) const {
						Matrix c;
						for(int i = 0; i < n; i++)
								for(int j = 0; j < n; j++)
										for(int k = 0; k < n; k++)
												c.a[i][k] = (c.a[i][k] + a[i][j] * ano.a[j][k]) % MOD;
						return c;
				}
} tmp, ans;

int Matrix::n = 0;

Matrix qpow(Matrix a, int b) { 
		Matrix tmp = Matrix(1) ; 
		for (; b; b >>= 1, a = a * a) if (b & 1) tmp = tmp * a ; 
		return tmp  ;
}

class MegaFactorial {
		public:
				int countTrailingZeros(int N, int K, int B) {
						if (B == 7) b = 7, cntb = 1;
						else if (B % 5 == 0) b = 5, cntb = 1;
						else if (B % 3 == 0) b = 3, cntb = (B == 9 ? 2 : 1);
						else b = 2, cntb = (B == 8 ? 3 : B == 4 ? 2 : 1);
						MOD = 1LL * MODU * cntb;
						tmp = Matrix() ; 
						tmp.n = K + 1 ; 
						for(int i = 1; i < tmp.n; i ++) for(int j = i; j < tmp.n; j ++) tmp.a[i][j] = 1;
						tmp.a[0][0] = 1;
						ans = Matrix(1);
						while (N) {
								ans = qpow(tmp, N % b) * ans;
								tmp = qpow(tmp, b);
								for(int i = 1; i < tmp.n; i ++)
										tmp.a[0][i]++;
								N /= b;
						}
						return ans.a[0][ans.n - 1] / cntb;
				}
} sol ;

int main() { 
		printf("%d\n", sol.countTrailingZeros(6, 1, 4)) ; 
}

