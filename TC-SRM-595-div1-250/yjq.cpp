#include <bits/stdc++.h>

using namespace std ;

const int MAXN = 1010; 

typedef long long LL ;

int cov[MAXN] ;
bool vis[MAXN]; 

class LittleElephantAndIntervalsDiv1 {
		public :
				LL getNumber(int n, vector<int> L, vector<int> R) {
					   int m = L.size() ;
					   for (int i = 0; i < m; i ++) for (int j = L[i]; j <= R[i];j ++) cov[j] = i + 1;  
					   for (int i = 1; i <= n; i ++) vis[cov[i]] = 1; 
					   LL ans = 1;
					   for (int i = 1; i <= m; i ++) ans <<= vis[i] ; 
					   return ans ;  
				}
} ;


