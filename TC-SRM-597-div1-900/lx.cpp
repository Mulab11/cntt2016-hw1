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

const int mo = 1e9 + 7;
const int N = 2e6 + 10;

inline int qpow(int x, int n) {
	int ans = 1;
	while (n) {
		if (n & 1)  ans = (LL) ans * x % mo;
		x = (LL) x * x % mo;
		n >>= 1;
	}
	return ans;
}

class LittleElephantAndBoard {
private :
	int pow2[N], fac[N], inv[N];

	inline int C(int n, int m) {
		return (LL) fac[n] * inv[m] % mo * inv[n - m] % mo;
	}
	inline void upd(int &x, int y) {
		(x += y) >= mo ? x -= mo : 0;
	}

	// 有 n 个空位，放入固定数量的 A B，A,B 不重复出现且每个空位都被填到的方案数
	// 有四类填法：ABA...BA, BAB...AB, ABAB..AB, BABA...BA，后两种可以一起计算
	int solve(int n, int A, int B) {
		if (n <= 0)  return 0;
		int ans = 0;
		rep (x0, 0, n) {		// 枚举填了多少 AB 或 BA，则另外两种填法可以 O(1) 计算
			int x1 = n - x0 + A - B;
			int x2 = n - x0 + B - A;
			if (x1 < 0 || x2 < 0 || (x1 & 1) || (x2 & 1))		// 判断方案合法性
				continue ;
			x1 >>= 1, x2 >>= 1;
			int r = A - x0 - x1;		// 首先给每个空位填入 "AB"、"A"、"B"，计算剩下多少 AB 可以用
			if (r < 0)  continue ;
			int tmp = (LL) fac[n] * inv[x0] % mo * inv[x1] % mo * inv[x2] % mo;
			tmp = (LL) tmp * C(n + r - 1, n - 1) % mo;		// 插板法计算给每个空位放入 AB 的方案数
			upd(ans, (LL) tmp * pow2[x0] % mo);		// 为了区分 "AB" 和 "BA"，方案数乘 2^x0
		}
		return ans;
	}
public :
	// 计数，枚举
	// 转换思路：重新定义每一列的"颜色"为这一列没有填的那个颜色  
	// 这样一来，相邻列的"颜色"仍然不同，且第一列确定、每一列的“颜色”确定，染色方法就能唯一确定
	int getNumber(int M, int A, int B, int C) {
		// 预处理阶乘、逆元、2的幂
		{
			int n = 2e6;
			fac[0] = 1;
			rep (i, 1, n)  fac[i] = (LL) fac[i - 1] * i % mo;
			inv[n] = qpow(fac[n], mo - 2);
			down (i, n, 1)  inv[i - 1] = (LL) inv[i] * i % mo;
			pow2[0] = 1;
			rep (i, 1, n)  (pow2[i] = pow2[i - 1] << 1) >= mo ? pow2[i] -= mo : 0;
		}
		A = M - A;		// 有 M-A 列没有填 A，下同
		B = M - B;
		C = M - C;
		// 计算思路：枚举序列两边"颜色"是否为 A，分情况计算。  
		LL ans = solve(A + 1, B, C) + 2ll * solve(A, B, C) + solve(A - 1, B, C);
		return 2ll * ans % mo;			// 第一列有两种填法，答案要乘 2
	}
};
