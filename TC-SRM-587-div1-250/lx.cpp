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

class JumpFurther {
private :
	inline int sum(int x) {
		return x * (x + 1) / 2;
	}
public :
	//贪心原则
	//先尝试每一步都走，如果会踩到坏格，不走第一步是最优的
	int furthest(int n, int m) {
		int i = 1;
		while (i < n && sum(i) < m) ++i;
		return sum(n) - (sum(i) == m);
	}
};
