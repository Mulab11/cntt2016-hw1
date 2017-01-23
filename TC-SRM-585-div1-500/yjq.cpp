#include <bits/stdc++.h>

#define MOD 1000000007 
using namespace std;

int n ;
const int MAXN = 3010 ; 

int f[MAXN] ; 

int C[MAXN][MAXN] ;

class LISNumber {
		public:
				int count(vector<int> a, int k) {
						n = 0 ; 
						for(int i = 0; i < a.size(); i ++) n += a[i];
						0[0[C]] = 1 ; 
						for (int i = 1; i < MAXN; i ++) { 
								0[i[C]] = 1 ; 
								for (int j = 1; j <= i; j ++) j[i[C]] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD ; 
						}
						for(int i = 1; i <= k; i++) {
								i[f] = 1 ; 
								for(int j = 0; j < a.size(); j++) f[i] = 1LL * f[i] * a[j][i[C]] % MOD ; 
								for(int j = 0; j < i; j++) f[i] = (f[i] + MOD - 1LL * f[j] * C[n + i - j][i - j] % MOD) % MOD;
						}
						return k[f] ; 
				}
} sol ;

int a[] = {1, 1, 1} ; 

vector<int> g ;

int main() { 
		for (int i = 0; i < 3; i ++) g.push_back(a[i]) ; 
		printf("%d\n", sol.count(g, 2)) ; 
}
