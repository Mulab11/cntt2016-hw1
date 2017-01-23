#include <bits/stdc++.h>

using namespace std ;

const int MAXN = 100010 ; 

class TheTree {
    public:
		int n, cnt[MAXN] ; 
		int maximumDiameter(vector<int> a) {
				n = a.size() ; 
				for (int i = 1;i <= n;i ++) cnt[i] = a[i - 1] ; 
				cnt[0] = 1;
			    int last = n + 1, ans = 0 ; 	
				for (int i = n ;i >= 0 ;i --) {
						ans = max(ans, n - i + last - 1 - i) ;
					    if (cnt[i] == 1) last = i ;  
				}
				return ans ; 
		}
};
			




				


