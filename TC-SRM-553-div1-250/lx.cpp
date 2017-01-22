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

class Suminator {
public :
	//大模拟术
	int findMissing(vector<int> pro, int want) {
		int cnt = 1;
		LL val = 0;
		down (i, pro.size()-1, 0) {
			int x = pro[i];
			if (x <= 0) {
				++cnt;
			} else {
				--cnt;
				val += pro[i];
			}
			if (!cnt)  break ;
		}
		if (val == want)  return 0;
		cnt = 1, val = 0;
		bool flag = 0;
		down (i, pro.size()-1, 0) {
			int x = pro[i];
			if (x == 0) {
				++cnt;
			} else {
				--cnt;
				if (x > 0) {
					val += x;
				} else {
					flag = 1;
				}
			}
			if (!cnt)  break ;
		}
		LL x = want - val;
		if (!flag) {
			return x ? -1 : 1;
		} else {
			return x >= 1 && x <= 1000000000 ? x : -1;
		}
	}
};
