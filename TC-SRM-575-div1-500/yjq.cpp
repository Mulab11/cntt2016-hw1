#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3010 ; 
int n, sum, x[MAXN];
class TheSwapsDivOne {
		public:
				double find(vector<string> seq, int k) {
						for(int i = 0; i < seq.size(); i++) {
								int l = seq[i].length() ; 
								for(int j = 0; j < l; j++) sum += x[n ++] = seq[i][j] - '0';
						}
						double t = pow(1.0 * (n - 3) / (n - 1), k) * (n - 1) / n + 1.0 / n ; 
						double ans = 0.0;
						for(int i = 0; i < n; i++) ans += (t * x[i] + (1.0 - t) / n * sum) * (i + 1) * (n - i);
						return ans / (n * (n + 1) / 2);
				}
};
