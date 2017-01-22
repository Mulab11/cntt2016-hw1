#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class SpaceWarDiv1 {
public :
	LL minimalFatigue(vector<int> S, vector<int> D, vector<LL> C) {
		int n = S.size(), m = D.size();
		sort(S.begin(), S.end());
		rep (i, 0, m - 1) {
			rep (j, i + 1, m - 1) {
				if (D[i] > D[j]) {
					swap(D[i], D[j]);
					swap(C[i], C[j]);
				}
			}
		}
		if (S[n - 1] < D[m - 1])  return -1;
		LL l = 1, r = 1e16;
		while (l <= r) {
			LL mid = (l + r) >> 1;
			int cur = m - 1;
			LL now = 0;
			down (i, n - 1, 0) {
				LL t = mid;
				while (cur >= 0) {
					if (S[i] < D[cur])  break ;
					if (C[cur] - now <= t) {
						t -= C[cur] - now;
						now = 0;
						cur--;
					} else {
						now += t;
						break ;
					}
				}
			}
			cur == -1 ? r = mid - 1 : l = mid + 1;
		}
		return l;
	}
};
