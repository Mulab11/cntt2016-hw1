#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010 ; 

bool vis[MAXN];

class TheSquareRootDilemma {
		public:
				int countPairs(int n, int m) {
						int ans = 0;
						for(int i = 2; i * i <= n; i ++) {
								for(int j = i * i; j <= n; j += i * i)
										vis[j] = true;
						}
						for(int i = 1; i <= n && i <= m; i++)  ans += (vis[i] ^ 1) * (int)sqrt(n / i) * (int)sqrt(m / i);
						return ans;
				}
};
