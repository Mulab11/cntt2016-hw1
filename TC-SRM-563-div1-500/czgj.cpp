#include <bits/stdc++.h>
using namespace std;

int A[120], N;
class SpellCards {
	public:
	int maxDamage(vector <int> level, vector <int> damage) {
		N = level.size();
		memset(A, 0, sizeof(A));
		// 0-1 knapsack
		for (int i = 0; i < N; ++i)
			for (int j = N - level[i]; j >= 0; --j)
				A[j + level[i]] = max(A[j] + damage[i], A[j + level[i]]);
		int ans = 0;
		for (int i = 0; i <= N; ++i) ans = max(ans, A[i]);
		return ans;
	}
};
