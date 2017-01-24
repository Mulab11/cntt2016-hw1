#include <bits/stdc++.h>

#define Mp 1000000007 

using namespace std; 

int N ;  

const int MAXN = 60 ;  

int dp[MAXN][2] ;  

bool cmp(int x, int y) {return x > y;  }

class DefectiveAddition {
		public:
				int count(vector <int> a, int n) {
						int m = a.size(); 

						sort(a.begin(), a.end(), cmp) ;  

						if (!a[0]) return n == 0; 


						for(N = 1; N * 2 <= a[0]; N <<= 1);  

						if (n >= (N << 1)) return 0; 
						memset(dp, 0, sizeof dp); 
						dp[1][0] = 1; 

						for(int i = 1; i < m; i ++)
								for(int p = 0; p < 2; p ++) {
										dp[i + 1][p] = (dp[i + 1][p] + dp[i][p] * 1LL * (min(a[i],N - 1) + 1)) % Mp;  
										if (a[i] >= N) dp[i + 1][p ^ 1] = (dp[i + 1][p ^ 1] + dp[i][p] * 1LL * (a[i] - N + 1)) % Mp; 
								}
						int ans = 0; 
						if (n & N) ans = dp[m][1];  else ans = dp[m][0]; 
						a[0] -= N; 
						n ^= N; 
						ans = (ans + count(a,n)) % Mp; 
						return ans; 
				}
} sol ;

vector<int> gx ; 
int main() { 
		gx.push_back(1), gx.push_back(2), gx.push_back(3) ; 
		printf("%d\n", sol.count(gx, 1)) ; 
}
