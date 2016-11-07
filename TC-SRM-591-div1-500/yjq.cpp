#include <bits/stdc++.h>

using namespace std ;

int gcd(int a, int b) {return b ? gcd(b, a % b) : a ;}

typedef long long LL ; 

class  PyramidSequences {
		public :
				LL distinctPairs(int n, int m) {
						n --, m -- ; 
						int d = gcd(n, m) ; 
						int x = n / d, y = m / d ; 
						return 1LL * (d - 1) * x * y + (1LL * (x + 1) * (y + 1) + 1) / 2 ; 
				}
} ;

					   		   
