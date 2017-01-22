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

template<typename T>
inline void read(T &x) {
	char c;
	while ((c = getchar()) < '0' || c > '9');
	for (x = c - '0'; (c = getchar()) >= '0' && c <= '9'; x = x * 10 + c - '0');
}

const int inf = 0x3f3f3f3f;
const int N = 1e5 + 10;

inline int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

class PyramidSequences {
public :
	// 数论
	// 把每个不同的数对看作二维平面上的一个点，可以发现 (A[i],B[i]) 在平面上画出了一条闭合的折线
	// 把只经过一次的点和经过多次的点分开统计
	LL distinctPairs(int n, int m) {
		n--, m--;
		int g = gcd(n, m);
		int x = n / g, y = m / g;
		LL s = (LL) x * y * (g - 1);					//只经过一次的点
		LL t = ((LL) (x + 1) * (y + 1) + 1) / 2;		//经过多次的点，(XXX + 1) / 2 实现了整数除法上取整
		return s + t;
	}
};

