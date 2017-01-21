#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std ;

typedef long long LL ;

const int MAXN = 2000010 ;

char s[MAXN] ;
int typ[MAXN] ; 
int f[MAXN];  

int prew[MAXN], preo[MAXN], pre[MAXN], nxt[MAXN], head = 0, tail = 0  ; 
class  WolfDelaymasterHard {

		int Solve(int N) {
				f[0] = 1;
				for (int i = 1;i <= N;i ++) {
					   if (s[i - 1] == '?') typ[i] = 0 ;
					   else if (s[i - 1] == 'w') typ[i] = 1; 
					   else typ[i] = 2;  
				}	
				for (int i = 1; i <= N + 1; i ++) { 
						prew[i] = prew[i - 1]; 
						preo[i] = preo[i - 1];  
					    if (typ[i - 1] == 1) prew[i] = i - 1 ; 
						else if (typ[i - 1] == 2) preo[i] = i - 1 ; 
				}
				tail = N + 1; 
				for (int i = 1; i <= N; i ++) { 
						f[i] = f[i - 1] ; 
						if (i & 1) {
								if (typ[i] == 2) { 			
									if (pre[tail]) nxt[pre[tail]] = i, pre[i] = pre[tail] ;
									pre[tail] = i, nxt[i] = tail ;
								}
								else if (typ[i] == 1) pre[tail] = 0 ;
								continue ; 
						}
						if (typ[i] == 1) {
								pre[tail] = 0 ; 
								continue ;  
						}
						if (pre[tail]) nxt[pre[tail]] = i, pre[i] = pre[tail] ;
						pre[tail] = i, nxt[i] = tail ; 
						for (int j = pre[tail] ; j; j = pre[j]) { 
								int lo = (i - j + 1) , hi = min(i - prew[j], (i - preo[j]) / 2) ; 
								if (lo > hi) {
										if (pre[j]) nxt[pre[j]] = nxt[j] ; 
										pre[nxt[j]] = pre[j] ; 
										continue ; 
								}
								int R = i - (lo << 1), L = i - (hi << 1) ; 
								if (L) (f[i] += (f[R] - f[L - 1] + MOD) % MOD) %= MOD ; 
								else (f[i] += f[R]) %= MOD ; 
						}
						if (typ[i] != 2) { 
								if (pre[tail] == i) {
										if (pre[i]) nxt[pre[i]] = tail ; 
										pre[tail] = pre[i] ;  
								}
						}
				}
				return (f[N] - f[N - 1] + MOD) % MOD ; 
							
		}	
		public : 
				int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
						for (int i = 0; i < N; i ++) {
								s[i] = '?' ;
						}
						LL x = w0 ;
						for (int i = 0; i < wlen; i ++) { 
								s[x] = 'w' ; 
								x = (x * wmul + wadd) % N;  
						}
						x = o0 ; 
						for (int i = 0; i < olen; i ++) { 
								s[x] = 'o' ; 
								x = (x * omul + oadd) % N ; 
						}
						return Solve(N) ; 
				}
} solution ; 

int main() { 
#ifdef YJQ_LOCAL
		freopen(".in", "r", stdin) ;
#endif
		int a, b, c, d, e, f, g, h, i; 
		scanf("%d%d%d%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f, &g, &h, &i) ; 
		printf("%d\n", solution.countWords(a, b, c, d, e, f, g, h, i) ) ; 
}


				
