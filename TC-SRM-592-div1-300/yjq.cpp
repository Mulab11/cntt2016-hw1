#include <bits/stdc++.h>

using namespace std ;

bool f[3], g[3] ; 

int getId(char a) { 
		if (a == 'R') return 0 ; 
		if (a == 'G') return 1; 
		if (a == 'B') return 2 ; 
}

class LittleElephantAndBalls {
		public : 
				int getNumber(string s) { 
						int n = s.length() ;  
						int now = 0, ans = 0  ; 
						for (int i = 0; i < n; i ++) { 
								ans += now ;  
								int typ = getId(s[i]) ; 
								if (!f[typ]) f[typ] = 1, now ++ ; 
								else if (!g[typ]) g[typ] = 1, now ++ ;  
						}
						return ans ; 
				}
} ; 


						
