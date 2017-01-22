/*
	Easy conclusion.
	To fix a bit we need at least one '0' and two '1's.
*/

#include <bits/stdc++.h>
using namespace std;

class TheDevice {
	public:
	int minimumAdditional(vector <string> plates) {
		int n = plates.size(), m = plates[0].size(), ret = 0;
		for (int i = 0; i < m; ++i){ // For each bit
			int cnt[2] = {0, 0};
			for (int j = 0; j < n; ++j) ++cnt[plates[j][i] & 1]; // Count '0's and '1's
			int t = max(1 - cnt[0], 0) + max(2 - cnt[1], 0);
			if (ret < t) ret = t; // Update
		}
		return ret;
	}
};

/*
	Bokura no 16 bit wars
	Sekai wo deki ni mawashitemo
		- Bokura no 16 bit wars
*/
