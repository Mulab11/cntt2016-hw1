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
const int N = 1e5 + 10;

class LittleElephantAndIntervalsDiv1 {
public :
	//计数，暴力
	//统计有多少次操作最后至少有一个位置没有被覆盖
	LL getNumber(int n, vector<int> L, vector<int> R) {
		int m = L.size();
		vector<bool> vis(m);
		LL ans = 1;
		rep (i, 1, n) {
			down (j, m-1, 0) {
				if (L[j] <= i && i <= R[j]) {
					if (!vis[j]) {
						vis[j] = 1;
						ans <<= 1;
					}
					break ;
				}
			}
		}
		return ans;
	}
};
