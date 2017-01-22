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

class TriangleXor {
public :
	// 容斥原理
	// 分层统计每个三角形对答案的贡献
	int theArea(int W) {
		double w = W, ans = 0;
		rep (i, 0, W) {
			double a = w / (W + i) * (W - i + 1);
			if (i > 0)  a *= 2.0;
			i & 1 ? ans -= a : ans += a;
		}
		return floor(ans * w / 2.0 + 1e-6);
	}
};
