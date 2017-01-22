/*
	Greedy.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class BitwiseAnd {
	public:
	vector<LL> lexSmallest(vector<LL> subset, int n) {
		vector<LL> empty; int m = subset.size();
		int cnt[66]; memset(cnt, 0, sizeof cnt);
		
		rep(i, 0, m - 1) rep(j, i + 1, m - 1)
			if (!(subset[i] & subset[j]))
				return empty;
		rep(i, 0, m - 1) rep(j, i + 1, m - 1) rep(k, j + 1, m - 1)
			if (subset[i] & subset[j] & subset[k])
				return empty;

		rep(i, 0, 59) rep(j, 0, m - 1) cnt[i] += subset[j] >> i & 1;
		rep(T, m, n - 1){
			LL t = 0;
			rep(i, 0, T - 1){ // fulfill A & t != 0
				int pos = -1;
				rep(j, 0, 59) if ((subset[i] >> j & 1) && cnt[j] < 2) {pos = j; break;}
				if (pos < 0) return empty;
				t ^= 1ll << pos; ++cnt[pos];
			}
			rep(i, T + 1, n - 1){ // make room for the following numbers 
				int pos = -1;
				rep(j, 0, 59) if (!cnt[j]) {pos = j; break;}
				if (pos < 0) return empty;
				t ^= 1ll << pos; ++cnt[pos];
			}
			subset.push_back(t);
		}
		sort(subset.begin(), subset.end());
		return subset;
	}
};

/*
	Nearly there!
*/
