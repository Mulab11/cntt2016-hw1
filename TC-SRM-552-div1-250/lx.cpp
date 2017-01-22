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

class FoxPaintingBalls {
public :
	// 分类讨论
	// 若 n%3=1，每个三角形里每种颜色球个数相同
	// 否则，每个三角形里有某种颜色的球恰好多一个
	// 解不等式即可
	LL theMax(LL R, LL G, LL B, int n) {
		if (n == 1)  return R + G + B;
		if (n % 3 == 1) {
			LL a = (LL) n * (n + 1) / 2, b = a / 3;
			return min(min(min(R, G), B) / b, (R + G + B) / a);
		} else {
			LL a = (LL) n * (n + 1) / 6;
			return min(min(R, G), B) / a;
		}
	}
};
