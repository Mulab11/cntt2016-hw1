#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class BitwiseAnd {
private :
	vector<LL> empty;
	LL bin[65];			// bin[i] = 2^i
	LL used, one;		// used：出现在两个数中的二进制位，one：只出现在一个数中的位
public :
	// 贪心，构造，二进制
	vector<LL> lexSmallest(vector<LL> subs, int n) {
		bin[0] = 1;
		rep (i, 1, 63)  bin[i] = bin[i - 1] << 1;
		int m = subs.size();
		rep (i, 0, m-1) {		// 判断给定集合是否合法
			one |= subs[i];
			rep (j, 0, i-1) {
				if ((subs[i] & subs[j]) == 0) {
					return empty;
				}
				used |= subs[i] & subs[j];
				rep (k, 0, j-1) {
					if ((subs[i] & subs[j] & subs[k])) {
						return empty;
					}
				}
			}
		}
		one ^= used;
		rep (k, m, n-1) {		// 逐个加入新的数，根据贪心原则，加入最少、最小的位
			LL now = 0;
			rep (j, 0, k-1) {	// 第 k 个数和之前每个数有一个共同的二进制位是最优的
				LL mask = one & subs[j];
				if (!mask) {
					return empty;
				}
				LL v = mask & -mask;
				one ^= v;
				used ^= v;
				now ^= v;
			}
			int res = n-k-1;
			rep (l, 0, res-1) {			// 第 k 个数需要和之后 res 个数之间各有一个共同的二进制位
				bool flag = 0;
				rep (j, 0, 59) {
					if (!(bin[j] & (used | one))) {
						now |= bin[j];
						one |= bin[j];
						flag = 1;
						break ;
					}
				}
				if (!flag)  return empty;
			}
			subs.pb(now);
		}
		sort(subs.begin(), subs.end());
		return subs;
	}
};
