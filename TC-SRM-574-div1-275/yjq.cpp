#include <bits/stdc++.h>

using namespace std ;

int n, m ;

const int MAXN = 20  ; 
int sa[MAXN], sb[MAXN] ; 

class TheNumberGame {
		public:
				bool check() { 
						for (int i = 1; i <= n - m + 1; i ++) {
								bool flag = 0 ; 
								for (int j = 1; j <= m; j ++) { 
										if (sa[i + j - 1] != sb[j]) flag = 1 ;
								}
								if (!flag) return 1; 
						}
						return 0 ; 
				}
				string determineOutcome(int a, int b) {
						while (a) sa[++n] = a % 10, a /= 10 ; 
						if (!a) sa[n = 1] = 0 ; 
						while (b) sb[++m] = b % 10, b /= 10 ; 
						if (!b) sb[n = 1] = 0 ; 
						if (check()) return "Manao wins" ; 
						reverse(sb + 1, sb + m + 1) ; 
						if (check()) return "Manao wins" ;
						return "Manao loses" ; 
				}
};

