#include <bits/stdc++.h>

#define MOD 1000000007 

using namespace std ;

int n, m ;

const int MAXN = 310 ; 

int L[MAXN], R[MAXN], pre[MAXN] ;

bool vis[MAXN] ;

vector<int> Parse(const vector<string> &vec) {
		string str;
		for(int i = 0; i < vec.size(); i++)
				str += vec[i];
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
int dp[MAXN][MAXN] ;
class WolfInZooDivOne {
		public:
				int count(int n, vector<string> _l, vector<string> _r) {
						vector<int> ll = Parse(_l), rr = Parse(_r);
						m = ll.size();
						for (int i = 0; i < m; i ++) L[i] = ll[i] + 1, R[i] = rr[i] + 1 ; 
						for (int i = 0; i < m; i ++) for (int j = 0; j < m; j ++) { 
								if (i == j) continue ; 
								if (L[j] <= L[i] && R[j] >= R[i] && R[j] - L[j] > R[i] - L[i]) vis[i] = 1 ; 
						}
						for (int i = 0; i < m; i ++) if (!vis[i]) pre[R[i]] = L[i] ; 

						int ans = 0 ; 
						dp[0][0] = 1;
						for(int i = 0; i <= n; i ++) {
								for(int j = i; j <= n; j ++) {
										ans = (ans + dp[i][j]) % MOD;
										int mx = j;
										for(int k = 0; k < m; k++)  {
												if(L[k] <= i) mx = max(mx, R[k]);
										}
										for(int k = mx + 1; k <= n; k++) dp[j][k] = (dp[j][k] + dp[i][j]) % MOD;
								}
						}
						return ans;
				}
} sol ;

vector<string> g[2] ; 

int main() { 
		g[0].push_back("0") ; 
		g[1].push_back("4") ; 
		printf("%d\n", sol.count(5, g[0], g[1])) ; 
}

