/*
	Binary search.
*/

#include <bits/stdc++.h>
#define MEM(x, y) memset(x, y, sizeof x)
using namespace std;
typedef long long LL;
class SpaceWarDiv1 {
	public:
	long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount) {
		LL cnt0[23333], cnt1[23333], cnt2[23333];
		MEM(cnt0, 0); MEM(cnt1, 0);
		int n = magicalGirlStrength.size(), m = enemyStrength.size();
		for (int i = 0; i < n; ++i) ++cnt1[magicalGirlStrength[i]]; // Count the girls
		for (int i = 0; i < m; ++i) cnt0[enemyStrength[i]] += enemyCount[i]; // Count the enemies
		LL l = 0, r = 1e16;
		while (l + 1 < r){ // Binary search
			LL m = (l + r) / 2;
			for (int i = 1; i <= 10000; ++i) cnt2[i] = cnt1[i] * m; // Update the count
			bool ok = 1; LL s0 = 0, s2 = 0;
			for (int i = 10000; i >= 1; --i)
				if ((s0 += cnt0[i]) > (s2 += cnt2[i])) // If there exists a suffix sum that s0 > s2, then fail
					{ok = 0; break;}
			(ok ? r : l) = m;
		}
		return r == 1e16 ? -1 : r;
	}
};

/*
	Ayatsurare kono ito
	Kieta toshitemo
	Ikanaite ikanaite
	Tsunaidete
		- Artificial Children  
*/
