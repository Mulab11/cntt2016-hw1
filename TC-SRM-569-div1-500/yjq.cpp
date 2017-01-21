#include <bits/stdc++.h>

using namespace std ; 

vector<int> tmp ; 
class TheJediTest { 
		public : 
				int minimumSupervisors(vector<int> a,int k) {
						tmp = a ; 
						int ans = 0 , cur = 0 ; 
						for (int i = 0; i < a.size(); i ++) {
								if (ans += a[i] / k, cur = a[i] % k) { 
										if (i + 1 < a.size()) {
												if (cur <= tmp[i]) a[i + 1] += cur ; 
												else a[i + 1] -= min(a[i + 1], k - cur), ans ++ ;
										}
										else ans ++ ; 
								}
						}
						return ans ; 
				}
};
