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

inline int inMod(int x, int mo) {
	if (x < 0)  x += mo;
	if (x >= mo)  x -= mo;
	return x;
}

// 复数类
struct comp {
	double x, y; 
	comp() {}
	comp(double x, double y) : x(x), y(y) {}
	inline comp operator + (const comp &b) const {
		return comp(x + b.x, y + b.y);
	}
	inline comp operator - (const comp &b) const {
		return comp(x - b.x, y - b.y);
	}
	inline comp operator * (const comp &b) const {
		return comp(x * b.x - y * b.y, x * b.y + y * b.x);
	}
};

// 复数相乘规则：模长相乘，辐角相加；取 sqrt 反之
comp sqrt(comp z) {
	double arg = atan2(z.y, z.x);
	arg /= 2.0;
	double len = sqrt(z.x * z.x + z.y * z.y);
	len = sqrt(len);
	return comp(len * cos(arg), len * sin(arg));
}
 
class SplittingFoxes2 {
private :
	// 存储单位根的幂
	comp w[30];
	int n;
	// 离散傅立叶变换
	vector<comp> DFT(vector<comp> V) {
		vector<comp> ans;
		rep (i, 0, n - 1) {
			comp sum(0, 0);
			rep (j, 0, n - 1) {
				comp z = V[j] * w[i * j % n];
				sum = sum + z;
			}
			ans.pb(sum);
		}
		return ans;
	}
	// 对复数进行 IDFT 之后再取整不一定是正确的，需要 O(n^2) 暴力卷积检验
	bool check(vector<int> v1, vector<int> v2) {
		rep (i, 0, n - 1) {
			int sum = 0;
			rep (j, 0, n - 1) {
				sum += v1[j] * v1[inMod(i - j, n)];
			}
			if (sum != v2[i])
				return 0;
		}
		return 1;
	}
public :
	// 数学，DFT
	// 循环卷积有：DFT(P) * DFT(P) = DFT(A), p = IDFT(sqrt(DFT(A)))
	// sqrt(A) 的每一项有两个取值，注意到 p 关于0 对称，所以 DFT(p) 关于 0 对称
	// 枚举量为 2^{n/2+1}  
	// n 没有特别的性质，计算 DFT 时 O(n^2) 暴力算  
	vector<int> getPattern(vector<int> tar) {
		n = tar.size();
		double alpha = 2.0 * acos(-1) / n;
		rep (i, 0, n - 1) {
			w[i] = comp(cos(alpha * i), sin(alpha * i));
		}
		vector<comp> V;
		rep (i, 0, n - 1) {
			V.pb(comp((double) tar[i] / (n * n), 0.0));
		}
		// 计算 sqrt(DFT(A))
		V = DFT(V);
		rep (i, 0, n - 1)  V[i] = sqrt(V[i]);
		// 之后均进行逆变换，单位根的幂取负
		rep (i, 0, n - 1)  w[i].y = -w[i].y;
		int m = n / 2 + 1;
		vector<int> ans;		// ans 记录字典序最优答案
		rep (s, 0, bin(m) - 1) {			//枚举 sqrt(DFT(A)) 的哪些项取反
			vector<comp> v2 = V;
			rep (i, 0, n - 1) {
				if (s & bin(min(i, n - i))) {
					v2[i] = comp(-v2[i].x, -v2[i].y);
				}
			}
			v2 = DFT(v2);
			vector<int> tmp;
			rep (i, 0, n - 1) {
				tmp.pb((int) (max(v2[i].x, 0.0) + 0.45865856387657545));
			}
			if (check(tmp, tar) && (ans.empty() || tmp < ans)) {
				ans = tmp;
			}
		}
		if (ans.empty()) {
			ans.pb(-1);
		}
		return ans;
	}
};
