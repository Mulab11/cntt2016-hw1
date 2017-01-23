#include <bits/stdc++.h>

using namespace std;

int n ; 

typedef long long LL ; 

const int MAXN = 60 ; 

string ss ;


static bool dp[MAXN][MAXN];

bool check(int l,int r) {
		l --,r --;
		LL x = 0;
		for(;l <= r;l ++) x = x * 2 + (ss[l] == '1');
		for(;x && x % 5 == 0;x /= 5);
		return x == 1;
}

class CuttingBitString {
		public:
				int getmin(string S) {
						ss = S ; 
						n = ss.length();
						memset(dp,0,sizeof dp);
						dp[0][0] = 1;
						for(int i = 1;i <= n;i ++) {
								for(int j = 1;j <= n;j ++) for(int k = 0;k < j;k ++)
										if (dp[i - 1][k] && S[k] == '1' && check(k + 1,j)) dp[i][j] = 1;
								if (dp[i][n]) return i;
						}
						return -1;
				}
} sol ;

int main() { 
		printf("%d\n", sol.getmin("1111101") ) ; 
}
