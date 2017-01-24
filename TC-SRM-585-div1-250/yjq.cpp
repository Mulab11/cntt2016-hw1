#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

const int MAXN = 1000010 ; 

int f[MAXN] ; 

class TrafficCongestion {
		public:
				int theMinCars(int x) {
						++ x ; 
						0[f] = 0, 1[f] = 1;  
						for(int i = 2, j = 0; i <= x; i ++) i[f] = ((j << 1) | 1) % MOD, (j += (i - 1)[f]) %= MOD ;
						return x[f] ; 
				}
} sol ;

int main() {
		printf("%d\n", sol.theMinCars(585858)) ; 
}
