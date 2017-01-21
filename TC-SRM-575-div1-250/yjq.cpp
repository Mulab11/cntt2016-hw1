#include <bits/stdc++.h>

using namespace std ;

typedef long long LL ; 

class TheNumberGameDivOne {
		public:
				string find(LL n) {
						if (n & 1) return "Burs" ; 
						while (n % 4 == 0) n /= 4 ; 
						if (n == 2) return "Burs" ;
						return "John" ; 
				}
};
