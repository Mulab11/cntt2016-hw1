#include <bits/stdc++.h>

using namespace std ;

int N ; 

vector<string> ans;

class FoxAndMp3 {
		public:
				void Dfs(int x) {
						if(ans.size() == 50 || x > N) return;
						char s[20];
						sprintf(s, "%d.mp3", x);
						ans.push_back(s);
						for(int i = 0; i <= 9; i++) Dfs(x * 10 + i);
				}
				vector<string> playList(int n) {
						N = n ; 
						for(int i = 1; i <= 9; i++) Dfs(i);
						return ans;
				}
};
