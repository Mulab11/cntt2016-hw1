#include <bits/stdc++.h>

using namespace std ;

int m ; 

const int MAXN = 16 ; 
const int MAXM = 60 ; 

int l[MAXN], r[MAXN], t[MAXN] ; 
int dp[MAXN][1 << MAXN] ;

int dis[MAXM][MAXM] ; 
vector<int> Parse(string str) {
		vector<int> ret;
		ret.push_back(0);
		for(int i = 0, j = 0; i < str.length(); i++)
		{
				if(str[i] == ' ')
						ret.push_back(0), j++;
				else
						ret[j] = ret[j] * 10 + (str[i] - '0');
		}
		return ret;
}

class TravellingPurchasingMan { 
		public : 
				int maxStores(int n, vector<string> store, vector<string> roads) { 
						m = store.size() ; 
						memset(dis, 0x3f, sizeof dis) ;
						for (int i = 0; i < n; i ++) dis[i][i] = 0 ; 
						vector<int> tmp ; 
						for (int i = 0; i < m; i ++) { 
								tmp = Parse(store[i]) ; 
								l[i] = tmp[0], r[i] = tmp[1], t[i] = tmp[2];  
						}
						for (int i = 0; i < roads.size(); i ++) {
								tmp = Parse(roads[i]) ; 
								int l = tmp[0], r = tmp[1], c = tmp[2] ; 
								dis[l][r] = min(dis[l][r], c) ;
								dis[r][l] = min(dis[r][l], c) ; 
						}
						for (int k = 0; k < n; k ++) {
								for (int i = 0; i < n; i ++) { 
										for (int j = 0; j < n; j ++) {
												dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]) ; 
										}
								}
						}
						int ans = 0 ;
						for (int i = 0; i < m; i ++) dp[i][1 << i] = dis[n - 1][i] ; 
						for (int i = 1; i < (1 << m); i ++) {
								for (int j = 0; j < m; j ++) { 
										if (dp[j][i] > 1000000000) continue ; 
										if (dp[j][i] <= r[i]) dp[j][i] = max(dp[j][i], l[i]) + t[i], ans = max(ans, __builtin_popcount(i)) ; 
										else continue ;  
										for (int k = 0; k < m; k ++) { 
												if (!((i >> k) & 1)) dp[k][i ^ (1 << k)] = min(dp[k][i ^ (1 << k)], dp[j][i] + dis[j][k]) ; 
										}
								}
						}
						return ans ;
				}
} ;
								


