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

const int N = 1e6 + 10;

inline int inMod(int x, int mo) {
	if (x < 0)   x += mo;
	if (x >= mo) x -= mo;
	return x;
}

class SparseFactorial {
private :
	// Min[i] 记录 x%m = i，且 m | f(x)，x 至少应该大于多少
	LL Min[N];
	int m;

	int pc[N], Cnt[N];
	LL A[N];

	// 对每个质数分别计算 Min，用最后合并即可
	void Work(pii u) {			// (u.first, u.second) = (p, c)
		int num = 1;
		rep (i, 1, u.y) num *= u.x;				// num = p^c
		memset(A, -1, sizeof(LL) * num);		// 记录 p^c 的Min数组
		memset(Cnt, 0, sizeof(int) * num);		// 辅助数组，Cnt[i] 存储 %p^c=i 的数中已经有多少个质因子 p
		memset(pc, 0, sizeof(int) * num);		// pc[i] 表示 i 中含有多少个质因子 p
		pc[0] = u.y;
		rep (i, 1, num / u.x-1) {
			pc[i * u.x] = pc[i] + 1;
		}
		rep (v, 0, u.x * u.y-1) {			// 对于 p^c 来说，只需要枚举前 c * p 个数即可
			LL to = (LL) v * v;
			int res = to % num, i = res;
			do {
				Cnt[i] += pc[inMod(i - res, num)];
				if (A[i] == -1 && Cnt[i] >= u.y) {
					A[i] = to;
				}
				i = inMod(i + u.x, num);
			} while (i != res);
		}
		rep (v, 0, num-1) {
			LL p = A[v] < 0 ? 1e18 : A[v];
			for (int c = v; c < m; c += num) {
				upmax(Min[c], p);
			}
		}
	}
public :
	// 数学，同余，CRT
	// 时间复杂度 O(m\log m)
	LL getCount(LL Low, LL High, LL m) {
		Low--;
		this->m = m;
		vector<pii> divs;
		int tmp = m;
		for (int i = 2; i*i <= tmp; ++i) {		//质因子分解
			if (tmp % i == 0) {
				int c = 1;
				while ((tmp /= i) % i == 0) ++c;
				divs.pb(mp(i, c));
			}
		}
		if (tmp > 1)  divs.pb(mp(tmp, 1));
		rep (i, 0, divs.size()-1) {				//分别计算每个质因子
			Work(divs[i]);
		}
		LL ans = 0;
		rep (i, 0, m-1) if (Min[i] <= High) {		//区间计数转化为前缀相减
			LL u = ((Min[i] - i + m) / m) * m + i;
			ans += (High - u + m) / m;
			if (u <= Low) {
				ans -= (Low - u + m) / m;
			}
		}
		return ans;
	}
};
