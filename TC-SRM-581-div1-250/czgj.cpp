/*
	Implementation.
	For every cell, check if it may (not) be monitored.
*/

#include <bits/stdc++.h>
#define MEM(x, y) memset(x, y, sizeof x)
using namespace std;
class SurveillanceSystem {
	public:
	string getContainerInfo(string containers, vector <int> reports, int L) {
		int sum[233], cnt0[233], cnt1[233], cnt2[233]; bool ok0[233], ok1[233]; string ret;
		MEM(sum, 0); MEM(cnt0, 0); MEM(cnt1, 0); MEM(ok0, 0); MEM(ok1, 0);
		int n = containers.length(), m = reports.size();
		for (int i = 0; i < m; ++i) ++cnt0[reports[i]]; // Count the demand
		for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + (containers[i - 1] == 'X'); // presum
		for (int i = n; i >= L; --i) ++cnt1[sum[i] -= sum[i - L]]; // Count the supply
		for (int i = L; i <= n; ++i) if (cnt0[sum[i]]) for (int j = i - L + 1; j <= i; ++j) ok1[j] = 1; // ok1 = can be monitored
		for (int i = 1; i <= n; ++i){
			bool ok = 1; int l = max(L, i), r = min(n, i + L - 1); memcpy(cnt2, cnt1, sizeof cnt2);
			for (int j = l; j <= r; ++j) if (--cnt2[sum[j]] < cnt0[sum[j]]) {ok = 0; break;}
			ok0[i] = ok; // ok0 = cannot be monitored
		}
		for (int i = 1; i <= n; ++i) ret += ok0[i] && ok1[i] ? '?' : ok0[i] ? '-' : '+'; // set string
		return ret;
	}
};

/*
	Kono gensokyo dewa joushiki ni torawaretewa ikenai no desune!
		- Kochiya Sanae
*/
