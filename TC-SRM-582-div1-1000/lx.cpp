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

const int N2 = 282842712;
const int N3 = 430886;
const int N4 = 16817;

typedef long long LL;

inline int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

class SemiPerfectPower {
private:
	bool P2[N3 + 3], P3[N4 + 3];		//P2、P3 分别表示无平方／立方因子数
	vector<int> cntP2[N3 + 3];				//cntP2[i][j] 表示 [1, ij] 中是 j 的倍数的无平方因子数
	vector<int> divs[N3 + 3];		//每个数的质因子
	
	inline int sqrt(const LL x) {
		int l = 1, r = N2;
		while (l <= r) {
			int mid = (l + r) >> 1;
			(LL) mid * mid <= x ? l = mid + 1 : r = mid - 1;
		}
		return r;
	}
	inline int cubert(const LL x) {
		int l = 1, r = N3;
		while (l <= r) {
			int mid = (l + r) >> 1;
			(LL) mid * mid * mid <= x ? l = mid + 1 : r = mid - 1;
		}
		return r;
	}

	inline LL calc(const LL n) {
		LL ans = 0;
		// 计算能表为 a * x^2 的数
		// 为避免重复计数，要求 a 没有平方因子
		// 需要满足 a < x
		for (int c = 1; (LL)c*c*c < n; ++c) if (P2[c])	
			ans += sqrt(n / c) - c;
		// 计算能表为 b * y^3 且不能表为 a * x^2 的数 (同样，要求 b 没有立方因子)
		// 这样的数满足条件：
		// b < y
		// 设 k 为 by 的最大平方因子，即 k^2 | by 且 P2[by / k^2]
		// 因不能表为 a * x^2，所以 by / k^2 >= y * k  ->  b >= k^3
		// 设 b' = b / gcd(k^2, b), k' = k^2 / gcd(k^2, b)，y' = y / k'
		// 那么 P2[by / k^2] 等价于 P2[b' * y']，等价于 P2[b'] && P2[y'] && gcd(b', y') == 1
		// 进一步转化 gcd(b', y') == 1，套一层反演即可
		for (int b = 1; (LL)b*b*b*b < n; ++b) if (P3[b]) {	
			for (int k = 1; k*k*k <= b; ++k) {
				int g = gcd(b, k * k);
				int _b = b / g, _k = k * k / g;
				if (!P2[_b])  continue ;
				int Down = b, Up = cubert(n / b);
				rep (s, 0, bin(divs[_b].size()) - 1) {
					int d = 1, mu = 1;
					rep (i, 0, divs[_b].size() - 1) {
						if (s & bin(i)) {
							d *= divs[_b][i], mu = -mu;
						}
					}
					ans += mu * (cntP2[d][Up / (_k * d)] - cntP2[d][Down / (_k * d)]);
				}
			}
		}
		return ans;
	}
public:
	//计数, 数论
	LL count(LL L, LL R) {	
		//预处理
		fill(P2 + 1, P2 + N3 + 1, true);
		for (int i = 2, v = i * i; v <= N3; ++i, v = i * i) {
			for (int j = v; j <= N3; j += v)  P2[j] = 0;
		}
		fill(P3 + 1, P3 + N4 + 1, true);
		for (int i = 2, v = i*i*i; v <= N4; ++i, v = i*i*i) {
			for (int j = v; j <= N4; j += v)  P3[j] = 0;
		}
		rep (i, 1, N3) {
			int l = N3 / i;
			cntP2[i].reserve(l + 1);
			cntP2[i][0] = 0;
			rep (j, 1, l)  cntP2[i][j] = cntP2[i][j - 1] + P2[i * j];
		}
		rep (i, 2, N4) {
			if (divs[i].empty()) {
				for (int j = i; j <= N4; j += i) 
					divs[j].pb(i);
			}
		}
		//区间计数转前缀相减
		return calc(R) - calc(L - 1);
	}
};
