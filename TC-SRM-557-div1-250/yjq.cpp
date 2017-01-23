#include<bits/stdc++.h>
using namespace std;
class FoxAndMountainEasy {
		public:
				string possible(int n,int a,int b,string s) {
						int mn = 0 ; 
						for (int i = 0; i < s.size(); i ++) {
								if (s[i] == 'U') a ++ ;
								else a -- ;
								mn = min(mn, a) ; 
						}

						a -= mn ; 
						n -= s.size() - mn ; 
						if (abs(a - b) <= n && (!((a - b + n) & 1))) return "YES" ;
						return "NO" ;
				}
} sol ; 

int main() {
		cout << sol.possible(4, 0, 4, "UU") << endl ; 
}
