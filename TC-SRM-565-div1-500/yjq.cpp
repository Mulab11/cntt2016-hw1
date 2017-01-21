#include <bits/stdc++.h>

using namespace std ; 


const int MAXN = 100010  ;  

typedef long long LL  ;  

bool is_prime[MAXN] ; 


void Init() {
		for(int i = 2 ; i < 50000 ; i ++) for(int j = i ; j <= 50000 / i ; j ++) is_prime[i * j] = 1 ; 
}
int d[MAXN * 10], st[MAXN * 10] ; 

int col[MAXN / 10] ; 

class TheDivisionGame {
		public:

				LL coluntWinningIntervals(int L, int R) {

						Init()  ;  
						for(int i = 0 ; i <= R - L ; i ++) st[i] = 1 ; 
						for(int i = 2 ;  i <= 50000  ;  i ++)
								if (!is_prime[i]) {
										for(int j = L / i + (bool) (L % i)  ;  j <= R / i ;  j ++) {
												int ref = i * j,c = 0,mu = 1 ; 
												for( ; ref % i == 0  ;  ref /= i) ++ c, mu *= i ; 
												d[i * j - L] += c,st[i * j - L] *= mu ; 
										}
								}
						LL ans = 0 ; 
						col[0] = 1 ; 
						for(int i = 0, cur = 0 ;  i <= R - L ;  i ++) {
								if (L + i != st[i]) ++ d[i] ;  
								cur ^= d[i] ; 
								ans += (R - L - i + 1) ; 
								ans -= col[cur] ; 
								col[cur] ++ ; 
						}
						return ans ; 
				}
} ; 
