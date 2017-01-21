#include <bits/stdc++.h> 

using namespace std ;

int n ;

const int MAXN = 60 ; 

int f[MAXN][MAXN] ;


class TravelOnMars {
		public :
				int minTimes(vector<int> a, int s, int t) { 
						n = a.size() ; 
						memset(f, 0x3f, sizeof f) ; 
						for (int i = 0; i < n; i ++) {
								for (int j = 0; j < a[i]; j ++) { 
										f[i][(i + j) % n] = f[i][(i - j + n) % n] = 1 ; 
								}
						}
						for (int k = 0; k < n; k ++) for (int i = 0; i < n ;i ++) for (int j = 0; j < n; j ++) f[i][j] = min(f[i][j], f[i][k] + f[k][j]) ; 
						return f[s][t] ; 
				}
} ; 



