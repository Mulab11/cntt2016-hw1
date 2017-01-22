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

class BigFatInteger {
public :
	// 数学，倍增，质因数分解
	// ans = 质因子个数 + [log_2 出现最多的质因子出现个数]
	int minOperations(int A, int B) {
		int cnt = 0, mx = 1;
		for (int i = 2; i * i <= A; ++i) {
			if (A % i == 0) {
				int c = 1;
				++cnt;
				while ((A /= i) % i == 0) ++c;
				upmax(mx, c);
			}
		}
		if (A > 1) ++cnt;
		mx = mx * B - 1;
		while (mx) {
			mx >>= 1;
			++cnt;
		}
		return cnt;
	}
};
