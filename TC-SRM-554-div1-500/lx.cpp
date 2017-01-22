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

vector<int> h;

inline bool cmp(const int x, const int y) {
	return h[x] < h[y] || (h[x] == h[y] && x < y);
}

class TheBrickTowerMediumDivOne {
public :
	//贪心
	//可以证明最优解中序列一定是一个“山谷”
	//按字典序最小构造解即可
	vector<int> find(vector<int> hei) {
		int n = hei.size();
		h = hei;
		vector<int> res(n);
		int cur = -1;
		rep (i, 0, n-1) {
			if (!i || h[i] <= h[res[cur]]) {
				res[++cur] = i;
			} else {
				res[n - i + cur] = i;
			}
		}
		sort(res.begin() + cur + 1, res.end(), cmp);
		return res;
	}
};
