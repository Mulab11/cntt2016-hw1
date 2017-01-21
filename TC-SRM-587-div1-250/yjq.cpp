#include <bits/stdc++.h>

using namespace std ;

class JumpFurther {
		public :
				int furthest(int N, int badStep) {
						int ans = N * (N + 1) / 2;  
						for (int i = 1; i <= N; i ++) {
								ans -= ((i * (i + 1) / 2) == badStep) ;
						}
						return ans ; 
				}
} ; 

