/*
	When the characters overlap,
	consider the characters that have to be equal,
	you can find that their indice is an arithmetic sequence, with common difference n - K.
*/

#include <bits/stdc++.h>
using namespace std;

class NewArenaPassword {
	public:
	int minChange(string oldPassword, int K) {
		int n = oldPassword.size(), ret = 0, k = n - K;
		int cnt[233];
		if (K == n) return 0; // Spj
		if (K * 2 <= n){ // Not overlapped : easy.
			for (int i = 0; i < K; ++i)
				ret += oldPassword[i] != oldPassword[n - K + i];
			return ret;
		}
		// Overlapped
		ret = n;
		for (int i = 0; i < k; ++i){
			// Get the indice, and find the one with the most appearence
			memset(cnt, 0, sizeof cnt);
			int t = 0;
			for (int j = i; j < n; j += k)
				t = max(t, ++cnt[oldPassword[j]]);
			ret -= t;
		}
		return ret;
	}
};

/*
	Now it's too late, too late to live
	only heaven loves you now
	so love it back for once
	just once
		- Cocaine
*/
