#include <bits/stdc++.h>

using namespace std ; 

typedef long long LL  ;  

const int MAXN = 60  ;  

int to[MAXN][MAXN][2]  ;  

vector<LL> ans ; 

class PastingPaintingDivOne {
		public:

				vector<LL> countColors(vector <string> chess, int T) {
						T -- ; 
						ans.resize(3,0) ; 
						int n = chess.size(),m = chess[0].length() ; 
						for(int i = 0 ; i < n ; i ++)
								for(int j = 0 ; j < m ; j ++) {
										if (chess[i][j] == '.') continue  ; 
										to[i][j][0] = max(i,0), to[i][j][1] = i + T  ; 
										for(int u = 0 ; u < i ; u ++)
												for(int v = 0 ; v < m ; v ++)
														if (i - j == u - v && chess[u][v] != '.')
																to[i][j][0] = max(to[i][j][0],to[u][v][1] + 1) ; 
										int bel ; 
										char c = chess[i][j]  ; 
										if (c == 'R') bel = 0 ; 
										if (c == 'G') bel = 1 ; 
										if (c == 'B') bel = 2 ; 
										ans[bel] += to[i][j][1] - to[i][j][0] + 1 ; 
								}
						return ans ; 
				}
} ; 
