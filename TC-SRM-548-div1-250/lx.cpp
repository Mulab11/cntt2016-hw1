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
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class KingdomAndTrees {
private :
	vector<int> h;
	int n;

	bool check(int v) {
		int p = 0;
		rep (i, 0, n-1) {
			if (h[i] + v <= p) return 0;
			p = max(h[i] - v, p + 1);
		}
		return 1;
	}
public :
	//二分 + 贪心验证
	//复杂度 O(n\log W)
	int minLevel(vector<int> h) {
		this->h = h;
		n = h.size();
		int l = 0, r = 1e9;
		while (l <= r) {
			int mid = (l + r) / 2;
			check(mid) ? r = mid - 1 : l = mid + 1;
		}
		return l;
	}
};
