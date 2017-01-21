#include <bits/stdc++.h>

using namespace std ;

int Calc(string a, string b) { 
		int l = 0 , la = a.length(), lb = b.length() ; 
		for (; l < la && l < lb && a[l] == b[l]; l ++)  ;
		return l ; 
}

class UndoHistory {
		public : 
				int minPresses(vector<string> a) { 
						int ans = a[0].length() + a.size() ; 
						for (int i = 1; i < a.size(); i ++) { 
								int tmp = 0 ; 
								if (Calc(a[i - 1], a[i]) == a[i - 1].length()) tmp = a[i - 1].length() + 2 ; 
								for (int j = 0; j < i; j ++) tmp = max(tmp, Calc(a[j], a[i])) ;
								ans += a[i].length() - tmp + 2 ; 
						}
						return ans ;
				}
} ;

