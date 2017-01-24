#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int dp[MAXN] ; 

class SpellCards {
		public:

				int maxDamage(vector<int> L, vector<int> D) {
						int n = L.size() ; 
						for(int i = 0;i < n;i ++) for(int j = n;j >= L[i];j --) dp[j] = max(dp[j], dp[j - L[i]] + D[i]);
						int ans = 0;
						for(int i = 0;i <= n;i ++) ans = max(ans, dp[i]);
						return ans;
				}
} sol ;

int a[] = {3, 3, 3} ; 

vector<int> g[2] ; 
int main() { 
		for (int i = 0; i < 3; i ++) g[0].push_back(a[i]) ; 
		a[0] = 10, a[1] = 20, a[2] = 30 ; 
		for (int i = 0; i < 3; i ++) g[1].push_back(a[i]) ; 
		cout << sol.maxDamage(g[0], g[1]) << endl ; 
}
