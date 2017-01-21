#include <bits/stdc++.h>

using namespace std ;

const int MAXN = 30 ; 

int fa[MAXN], cnt[MAXN] ;

vector<int> g[MAXN]; 
int findfa(int x) {
		return fa[x] == x ? x : fa[x] = findfa(fa[x]);
}

class GooseTattarrattatDiv1 {
		public : 
				int getmin(string s) { 
						int n = s.length() ;
						for (int i = 0; i < 26; i ++) fa[i] = i ; 
						int ans = 0 ;  
						for (int i = 0; i + i < n; i ++) {
								int w1 = s[i] - 'a', w2 = s[n - 1 - i] - 'a';
							    cnt[w1] ++; 
								if (n - 1 - i != i) cnt[w2] ++ ; 
								if (findfa(w1) != findfa(w2)) fa[findfa(w1)] = findfa(w2) ; 
						}
						for (int i = 0; i < 26; i ++) {
								g[findfa(i)].push_back(cnt[i]) ; 
						}
						for (int i = 0; i < 26; i ++) { 
								if (!g[i].size()) continue ;
								sort(g[i].begin(), g[i].end()) ; 
								for (int j = 0; j < g[i].size(); j ++) { 
										ans += g[i][j] ; 
								}
								ans -= g[i][g[i].size() - 1] ; 
						}
						return ans ; 
				}
} ;



