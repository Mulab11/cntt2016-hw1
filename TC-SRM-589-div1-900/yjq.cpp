#include <bits/stdc++.h>

using namespace std ;

int n = 0 ;
const int MAXN = 310 ;
const int MAXS = 1 << 17 ; 

char s[MAXN]; 

int dp[2][MAXS] ; 

int Solve1(int M) {
	   int p = 0 ;
	   const int INF = 1000000007 ; 
	   for (int i = 1, r = 1; i <= n; i = r + 1, r = i) { 
				r = min(n, i + M - 1) ; 
				int now = 0 , len = r - i + 1;  
				for (int j = i; j <= r; j ++) now = now * 2 + s[j] - '0' ; 
				for (int j = 0; j < (1 << M); j ++) dp[p ^ 1][j] = INF ;
			    for (int j = 0; j < (1 << M); j ++) { 
						int tmp = __builtin_popcount((j >> (M - len)) ^ now) ; 
						dp[p ^ 1][j] = min(dp[p ^ 1][j], dp[p][j] + tmp) ; 
						dp[p ^ 1][j ^ ((1 << M) - 1)] = min(dp[p ^ 1][j ^ ((1 << M) - 1)], dp[p][j] + len - tmp + 1) ; 
				}
				p ^= 1 ;
	   }	
	   int ans = 1 << 30 ;
	   for (int i = 0; i < (1 << M); i ++) ans = min(ans, dp[p][i] ) ; 
	   return ans ; 		
}

int Solve2(int M) { 
		int wid = n / M - (n % M == 0) ; 
		int ans = 1 << 30 ; 
		for (int i = 0; i < (1 << wid); i ++) { 
				int tmp = __builtin_popcount(i) ; 
				for (int j = 1; j <= M; j ++) { 
						int cur = j , now = 0, tmp2 = 0, tmp3 = 0 ; 
						for (int k = 0; cur <= n; k ++, cur += M) {
								tmp2 += (s[cur] - '0' != now) ; 
								tmp3 += (s[cur] - '0' == now) ;  
								now ^= ((i >> k) & 1) ;
						}
						if (tmp2 > tmp3) tmp += tmp3 ;
						else tmp += tmp2 ; 
				}
				ans = min(ans, tmp) ; 
		}
		return ans ; 
}


class FlippingBitsDiv1 {
		public :
				int getmin(vector<string> sp , int M) { 
						int sz = sp.size() ; 
						for (int i = 0; i < sz; i ++) { 
								int tn = sp[i].length() ;
								for (int j = 0; j < tn; j ++) { 
										s[++n] = sp[i][j] ; 
								}
						}
						if (M * M <= n) return Solve1(M) ;
						else return Solve2(M) ; 
				}
} solution ;

vector<string> g; 

string a[110] = {"1001011000101010001111111110111011011100110001001"} ; 

int main() {
		g.push_back(a[0]) ; 
		printf("%d\n", solution.getmin(g, 2)) ;
}

