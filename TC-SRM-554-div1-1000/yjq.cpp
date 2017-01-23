#include <bits/stdc++.h>

#define MOD 1234567891

using namespace std; 

const int MAXN = 130 ;  

struct Matrix {
		int n ;  

		int a[MAXN][MAXN];  
		void init(int N = 121) {
				n = N; 
				memset(a,  0,  sizeof a); 
		}
		int* operator[](int x) {
				return a[x]; 
		}
		void Init_I() {
				for(int i = 0; i < n; i ++) a[i][i] = 1; 
		}
		Matrix operator * (const Matrix ano) const {
				Matrix c; 
				c.init(); 
				for(int i = 0; i < n; i ++)
						for(int k = 0; k < n; k ++)
								if (a[i][k])
										for(int j = 0; j < n; j ++)
												if (ano.a[k][j])
														c[i][j] = (c[i][j] + 1LL * a[i][k] * ano.a[k][j] % MOD) % MOD ; 
				return c; 
		}


} a0,  tmpf; 


int trans1[20][5] ; 

int bel[10] ;  

int tot = 0 ;  

int wangyurzee = 0 ; 

int qghgdshh = 0 ;  

typedef long long LL ;  


void Init1(int n, int m) {
		if (n == 4) {
				++ tot; 
				for(int i = 0; i < 4; i ++) trans1[tot - 1][i] = bel[i]; 
				trans1[tot - 1][4] = m; 
				return; 
		}
		for(int i = 0; i < m; i ++) bel[n] = i, Init1(n + 1, m); 
		bel[n] = m, Init1(n + 1, m + 1); 
}



void Init2(int n, int m) {
		if (n == 4) {
				int tmpc = 1; 
				for(int i = trans1[qghgdshh][4]; i < m; i ++) 
						tmpc = (tmpc * 1ll * (wangyurzee - i)) % MOD; 
				static int ns[4]; 
				ns[0] = 0; 
				int nm = 1, nxt; 
				for(int i = 1; i < 4; i ++) {
						bool get = 0; 
						for(int j = 0; j < i; j ++) if (bel[i] == bel[j]) {ns[i] = ns[j]; get = 1; break; }
						if (!get) ns[i] = nm ++; 
				}
				for(int i = 0; i < tot; i ++) {
						bool eq = 1; 
						for(int j = 0; j < 4; j ++) if (ns[j] != trans1[i][j]) {eq = 0; break; }
						if (eq) {nxt = i; break; }
				}
				int cnt = 0;  
				for(int i = 0; i < 4; i ++) if (bel[i] == trans1[qghgdshh][i]) ++ cnt; 
				for(int i = 0; i < 4; i ++) if (bel[i] == bel[(i + 1) % 4]) ++ cnt; 
				for(int k = 0; k < 8; k ++) if (k + cnt > 7) break;  
				else a0[k * tot + qghgdshh][(k + cnt) * tot + nxt] = (tmpc + 0ll + a0[k * tot + qghgdshh][(k + cnt) * tot + nxt]) % MOD; 
				return; 
		}
		for(int i = 0; i < m; i ++) bel[n] = i, Init2(n + 1, m); 
		bel[n] = m, Init2(n + 1, m + 1); 
}
class TheBrickTowerHardDivOne {
		public:

				int find(int C,  int K,  LL H) {
						wangyurzee = C; 
						a0.init(); tmpf.init(); 
						Init1(0, 0); 
						for(int i = 0; i < tot; i ++) {
								int cnt = 0, bas = 1; 
								for(int j = 0; j < trans1[i][4]; j ++) bas = bas * 1ll * (wangyurzee - j) % MOD; 
								for(int j = 0; j < 4; j ++)
										if (trans1[i][j] == trans1[i][(j + 1) % 4]) ++ cnt; 
								tmpf[0][cnt * tot + i] = bas;  
						}
						for(int i = 0; i < tot; i ++) {
								qghgdshh = i; 
								Init2(0, trans1[i][4]); 
						}
						for(int k = 0; k < (K + 1) * tot; k ++)
								a0[k][tot << 3] = 1; 
						a0[tot << 3][tot << 3] = 1; 
						while (H) {
								if (H & 1) tmpf = tmpf * a0; 
								a0 = a0 * a0; 
								H >>= 1 ;  
						}
						return tmpf[0][tot << 3]; 
				}
} sol ;

int main() {} 
