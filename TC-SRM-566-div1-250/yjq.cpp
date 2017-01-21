#include <bits/stdc++.h>

using namespace std;

const int MAXN = 60 ; 

typedef long long LL ; 

bool a[MAXN][MAXN];

int due[MAXN] ;

class PenguinSledding {
		public:
				LL countDesigns(int n, vector<int> x, vector<int> y) {

						int m = x.size();
						
						for(int i = 0; i < m; i ++) {
								a[x[i]][y[i]] = a[y[i]][x[i]] = 1;
								due[x[i]] ++, due[y[i]] ++ ; 
						}
						LL ans = m + 1 ; 
						for (int i = 1; i <= n; i ++) for (int j = i + 1; j <= n; j ++) { 
								if (a[i][j]) for (int k = j + 1; k <= n; k ++) {
										if (a[j][k] && a[i][k]) ans ++ ; 
								}
						}
						for (int i = 1 ; i <= n ; i ++)  ans += (1LL << due[i]) - 1 - due[i] ; 
						return ans;
				}
};
