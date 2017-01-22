/*
	Implementation.
*/

#include <bits/stdc++.h>
using namespace std;
const int offset = 1000; // offset to handle negative indices
int n, m;
int sum1[50][50], sum2[50][50];
int mxd[50][2000], mxu[50][2000]; // up and down
class FoxAndFlowerShopDivOne {
	public:
	int solve(vector <string> flowers, int maxDiff){
		n = flowers.size(); m = flowers[0].length();
		memset(sum1, 0, sizeof sum1); memset(sum2, 0, sizeof sum2);
		memset(mxd, 0xf0, sizeof mxd); memset(mxu, 0xf0, sizeof mxu); // illegal = -inf
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
			sum1[i + 1][j + 1] = sum1[i][j + 1] + sum1[i + 1][j] - sum1[i][j] + (flowers[i][j] == 'L'),
			sum2[i + 1][j + 1] = sum2[i][j + 1] + sum2[i + 1][j] - sum2[i][j] + (flowers[i][j] == 'P');
		int mind = 23333, maxd = -23333;
		for (int i1 = 0; i1 < n; ++i1) for (int i2 = i1 + 1; i2 <= n; ++i2)
			for (int j1 = 0; j1 < m; ++j1) for (int j2 = j1 + 1; j2 <= m; ++j2){
				int s1 = sum1[i2][j2] - sum1[i1][j2] - sum1[i2][j1] + sum1[i1][j1];
				int s2 = sum2[i2][j2] - sum2[i1][j2] - sum2[i2][j1] + sum2[i1][j1];
				int ss = s1 + s2, delta = s1 - s2;
				if (mind > delta) mind = delta;
				if (maxd < delta) maxd = delta;
				delta += offset;
				mxd[i1][delta] = max(mxd[i1][delta], ss);
				mxu[i2][delta] = max(mxu[i2][delta], ss);
			}
		for (int i = n - 2; i >= 0; --i) for (int j = offset + mind; j <= offset + maxd; ++j)
			mxd[i][j] = max(mxd[i + 1][j], mxd[i][j]);
		for (int i = 2; i <= n; ++i) for (int j = offset + mind; j <= offset + maxd; ++j)
			mxu[i][j] = max(mxu[i - 1][j], mxu[i][j]);
		int ret = -23333;
		for (int i = 1; i < n; ++i) for (int j = mind; j <= maxd; ++j){
			int k1 = max(mind, -maxDiff - j), k2 = min(maxd, maxDiff - j); 
			for (int k = k1; k <= k2; ++k){
				int tans = mxd[i][j + offset] + mxu[i][k + offset];
				if (tans > ret) ret = tans;
			}
		}
		return ret < 0 ? -1 : ret;
	}
	vector<string> rot(const vector<string>& flowers){ // rotate the map
		int n = flowers.size(), m = flowers[0].length(); 
		vector<string> ret(m, string(n, ' '));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				ret[j][i] = flowers[i][j];
		return ret;
	}
	int theMaxFlowers(vector <string> flowers, int maxDiff) {
		return max(solve(flowers, maxDiff), solve(rot(flowers), maxDiff));
	}
};

/*
	'Nanigenaku miageta
	tsuki ga hora kirei de...'
		- Touchuu Aika
*/
