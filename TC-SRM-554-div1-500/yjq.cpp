#include <bits/stdc++.h>
using namespace std;

int n ; 

const int MAXN = 60 ;

int tmp[MAXN] ;

class TheBrickTowerMediumDivOne {
		public:
				vector<int> find(vector<int> h) {
						n = h.size() ; 
						int mx = 50 ; 
						for (int i = 0; i < n; i ++) {
							   int l = 0 ;
								while (l < n && h[l] > mx) l ++ ; 
								if (l == n) { 
										l = 0 ;
										for (int j = 0; j < n; j ++) if (h[j] < h[l]) l = j ; 
								}
								else mx = h[l] ; 
								h[l] = 50 ; 
								tmp[i] = l ; 
						}
						vector<int> ans ; 
						for (int i = 0; i < n; i ++) ans.push_back(tmp[i]) ; 
						return ans ; 
				}

} ; 	

