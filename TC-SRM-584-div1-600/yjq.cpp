#include <bits/stdc++.h>

using namespace std;

int n = 0 ;

typedef long long LL ; 

const int MAXN = 1000010 ; 
const int MAXM = 60 ;

int S[MAXN], trans[MAXM];

bool fg[MAXM];

LL pre[MAXM] ; 

LL C[MAXM][MAXM];

LL dp[MAXM][MAXM] ;

vector<pair<int, int> > v;

class Excavations {
		public:
				LL count(vector<int> K, vector<int> dep, vector<int> fd, int k) {
						n = K.size();

						for(int i = 0; i < n; i++) S[dep[i]]++;
						for(int i = 1; i <= 100000; i++) S[i] += S[i - 1];
						for(int i = 0; i < n; i++) dep[i] = S[dep[i]];

						0[0[C]] = 1 ; 
						for(int i = 0; i <= n; i ++) {
								0[i[C]] = 1 ; 
								for(int j = 1; j <= i; j ++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
						}
						for(int i = 0; i < fd.size(); i ++) fg[fd[i]] = 1;
						for(int i = 0; i < n; i++) if(fg[K[i]]) v.push_back(make_pair(K[i], dep[i]));

						sort(v.begin(), v.end()) ;
						trans[v.size()] = v.size() ;
						int tp = v.size() ; 
						for(int i = tp - 1; ~i; i--) {
								trans[i] = trans[i + 1];
								if(i + 1 < tp&& v[i].first != v[i + 1].first) trans[i] = i + 1;
						}
						LL ans = 0 ; 
						int cur = 0 ;
						for(int d = n + 1; ~d ; d--) {
								for(int i = 0; i < n; i ++) if(dep[i] == d && !fg[K[i]]) cur ++ ; 
								dp[0][0] = 1;
								for(int i = 0; i < tp; i ++) {
										for(int j = 0; j <= tp; j ++) {
												if (dp[i][j]) { 
														if (v[i].second < d) dp[trans[i]][j + 1] += dp[i][j];
														if (i + 1 < tp && v[i + 1].first == v[i].first) {
																dp[i + 1][j] += j[i[dp]] ;
																dp[i + 1][j + 1] += j[i[dp]];
														}
												}
										}
								}
								for(int i = 0; i <= k; i ++) ans += dp[tp][k - i] * (i[cur[C]] - i[pre]), i[pre] = i[cur[C]];
						}
						return ans;
				}
} sol ; 

