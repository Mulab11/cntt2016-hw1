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

const int inf = 0x3f3f3f3f;
const int M = 2501 * 2501;
 
class FindPolygons {
private :
	int w[M + 5];
	int A[10144];
	int B[10144];
	inline int sqr(int x) {
		return x * x;
	}
public :
	// 枚举，结论
	// 每条边的长度均为整数
	// L 为奇数时无解，L 为偶数时至少能找到合法的矩形
	// 只需要检验是否有合法的三角形即可
	double minimumPolygon(int L) {
		memset(w, -1, sizeof(w));
		rep (i, 1, 2501)  w[sqr(i)] = i;		//存下所有完全平方数
		int tot = 0;
		int minlen = 1;
		int maxlen = L / 2;
		rep (c, minlen, maxlen) {		//预处理所有整数长度的合法线段
			rep (a, 0, c) {
				int b2 = sqr(c) - sqr(a);
				if (w[b2] != -1) {
					A[tot] = a;
					B[tot++] = w[b2];
				}
			}
		}
		int best = inf;
		rep (i, 0, tot-1) {				// 固定第一个点在原点，枚举两个点的坐标，判断合法性
			rep (j, i+1, tot-1) {
				int x1 = A[i], y1 = B[i];
				int x2 = A[j], y2 = B[j];
				int dx = x2 - x1, dy = y2 - y1;
				int c2 = sqr(dx) + sqr(dy);
				if (c2 <= M && w[c2] != -1 && x1 * y2 - x2 * y1 != 0) {		// 满足条件当且仅当 c 为整数、三点不共线
					int p = w[sqr(A[i]) + sqr(B[i])];
					int q = w[sqr(A[j]) + sqr(B[j])];
					int r = w[sqr(dx) + sqr(dy)];
					if (p + q + r == L) {			// 周长是否恰为 L
						upmin(best, max(max(p, q), r) - min(min(p, q), r));
					}
				}
			}
		}
		if (best < inf) {
			return (double) best;
		} else {
			if ((L & 1) || (L == 2)) {
				return -1.0;
			}
		}
		return L % 4 == 0 ? 0.0 : 1.0;
	}
};
