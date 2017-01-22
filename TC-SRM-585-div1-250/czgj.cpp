/*
	f[0] = f[1] = 1
	f[i] = 2 * f[i - 1] + (-1) ^ i
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
class TrafficCongestion {
	public:
	int theMinCars(int treeHeight) {
		int f = 1;
		for (int i = 1; i <= treeHeight; ++i)
			f = (f * 2 + (i & 1 ? -1 : 1)) % MOD;
		if (f < 0) f += MOD;
		return f;
	}
};

/*
	Shiawase wo kanjita toki wa
	Itsumo tonari ni ongaku ga afuretete
		- Nanairo Aniversary
*/
