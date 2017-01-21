#include <bits/stdc++.h>

using namespace std ;

const int MAXN = 1000010 ; 

bitset<MAXN> dp ;  
class MayTheBestPetWin {
		public :
				int calc(vector<int> A, vector<int> B) { 
						int n = A.size() ; 
						dp.set(0) ;
					    int tota = 0, totb = 0;  	
						for (int i = 0; i < n; i ++) { 
								tota += A[i], totb += B[i] ;  
								dp |= (dp << (A[i] + B[i])) ; 
						}
						int ans = 1 << 30 ; 
						for (int i = 0; i <= tota + totb;i ++) { 
								if (dp[i]) {
									   ans = min(ans, max(i - tota, totb - i)) ;
								}
						}
						return ans ; 
				}
} ; 




