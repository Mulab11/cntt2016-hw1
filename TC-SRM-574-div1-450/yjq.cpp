#include <bits/stdc++.h>

using namespace std;

typedef long long LL ; 


const int MAXN = 19 ;

LL dp[1 << MAXN][MAXN] ;

int sta[MAXN], cnta, stb[MAXN], cntb, tmp[MAXN] ; 

inline void update(LL &a, LL b) { a += b; } 
class PolygonTraversal {
		public:
				long long count(int n, vector <int> p) {

						int tot = 0 ; 
						for (int i = 0; i < p.size(); i ++) tot |= (1 << (-- p[i])) ; 
						dp[tot][p[p.size() - 1]] = 1 ; 
						for(int i = tot; i < (1 << n); i ++) {
								cnta = cntb = 0 ; 
								for (int j = 0; j < n; j ++) {
										tmp[j] = (j ? tmp[j - 1] : 0) ; 
										if ((i >> j) & 1) sta[cnta ++] = j , tmp[j]++ ; 
										else stb[cntb ++] = j  ;
								}
								for (int j = 0; j < cnta; j ++) { 
										if (dp[i][sta[j]]) { 
												for (int k = 0; k < cntb; k ++) { 
														int x = max(sta[j], stb[k]), y = sta[j] + stb[k] - x ; 
														if (tmp[x - 1] - tmp[y] && tmp[x - 1] - tmp[y] < tmp[n - 1] - 1) update(dp[i | (1 << stb[k])][stb[k]], dp[i][sta[j]]) ; 

												}
										}
								}
						}
						LL ans = 0;
						for(int i = 0; i < n; i ++) if(i != p[0] && i != (p[0] + 1) % n && i != (p[0] - 1 + n) % n)
										ans += dp[(1 << n) - 1][i];
						return ans;
				}
};
