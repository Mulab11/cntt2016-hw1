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

class TheTree {
public :
	//枚举
	//直径的一个端点深度一定为 n, 枚举另一个端点的深度, 最小化它们的Lca的深度
	int maximumDiameter(vector<int> cnt) {
		int n = cnt.size();
		int h = 0, ans = n;
		rep (i, 0, n-1) {
			if (cnt[i] == 1) {
				h = i + 1;
			}
			upmax(ans, n + i + 1 - h * 2);
		}
		return ans;
	}
};
