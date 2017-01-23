#include <bits/stdc++.h>

using namespace std;

class FoxAndChess {
		public:
				string ableToMove(string s, string t) {
						string s1, s2;
						vector<int> p1, p2;
						for(int i = 0; i < s.length(); i++) if(s[i] != '.') s1 += s[i], p1.push_back(i);
						for(int i = 0; i < t.length(); i++) if(t[i] != '.') s2 += t[i], p2.push_back(i) ;
						if(s1 != s2) return "Impossible";
						for(int i = 0; i < s1.size(); i++) {
								if(s1[i] == 'L') {
										if(p1[i] < p2[i]) return "Impossible";
								}
								else {
										if(p1[i] > p2[i]) return "Impossible";
								}
						}
						return "Possible";
				}
} sol ;


string a = ".L.R.R." ; 

string b = 
"L...R.R" ; 

int main() { 
		cout << sol.ableToMove(a, b) << endl ; 

}
