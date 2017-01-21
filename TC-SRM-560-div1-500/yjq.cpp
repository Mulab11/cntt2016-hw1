#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310 ; 

int pnts[MAXN][MAXN], dp[MAXN][MAXN] ; 

const int LIMIT = 300;  
class DrawingPointsDivOne {
		public:
		bool check(int k) {
				for(int i = LIMIT - 1; i > 0; i --) for(int j = LIMIT - 1; j > 0; j --) 
							if(!pnts[i][j]) pnts[i][j] = pnts[i - 1][j] || pnts[i][j - 1] || pnts[i - 1][j - 1];
				for(int i = LIMIT - 2; i > 0; i --) 
						for(int j = LIMIT - 2; j > 0; j --) {
								dp[i][j] = pnts[i][j] ? min(dp[i + 1][j + 1], min(dp[i + 1][j], dp[i][j + 1])) + 1 : 0;
								if(pnts[i][j] < 2 && dp[i][j] > k)
										return 0 ;
						}
				return 1 ;
		}
		int maxSteps(vector<int> x, vector<int> y) {
				for(int i = 0; i < x.size(); i ++) pnts[x[i] + 71][y[i] + 71] = 2;
				for(int len = 1; len <= 150; len ++) if(!check(len)) return len - 1;
				return -1 ; 
		}
};
