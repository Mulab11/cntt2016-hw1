#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class PolygonTraversal{
public:
	LL dp[(1 << 18) + 5][19]; int N;
	inline bool check(int i, int j, int k){
		if(i & (1 << k)) return false;
		i ^= 1 << j; if(j > k) swap(j, k);
		int mid = (1 << (k + 1)) - (1 << j);
		if((i & mid) == 0 || (i & (mid ^ (N - 1))) == 0) return false;
		return true;
	}
	LL count(int n, vector <int> prev){
		int i, j, k; LL ans = 0LL, cur;
		memset(dp, 0, sizeof(dp));
		for(i = j = 0; i < int(prev.size()); ++ i)
			j |= 1 << (prev[i] - 1);
		dp[j][prev.back() - 1] = 1LL;
		for(N = 1 << n, i = 0; i < N; ++ i)
			for(j = 0; j < n; ++ j){
				if((cur = dp[i][j]) == 0LL) continue;
				for(k = 0; k < n; ++ k)
					if(check(i, j, k))
						dp[i | (1 << k)][k] += cur;
			}
		for(i = 0; i < n; ++ i)
			if((i - prev[0] + n) % n != 1 && (i - prev[0] + n) % n != n - 1)
				ans += dp[N - 1][i];
		return ans;
	}
};
