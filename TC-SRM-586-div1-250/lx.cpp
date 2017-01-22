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

class PiecewiseLinearFunction {
private :
	vector<int> val;
	int n;
public :
	//枚举
	//枚举不同的Y，求交点个数即可
	int maximumSolutions(vector<int> Y) {
		n = Y.size();
		rep (i, 1, n-1) {
			if (Y[i] == Y[i - 1]) {
				return -1;
			}
		}
		int ans = 0;
		val = Y;
		sort(val.begin(), val.end());
		val.erase(unique(val.begin(), val.end()), val.end());
		for (int v : val) {
			int tmp = 0;
			rep (i, 0, n-1) {
				tmp += Y[i] == v;
				if (i) {
					if (Y[i - 1] > v) {
						tmp += Y[i] < v;
					} else if (Y[i - 1] < v) {
						tmp += Y[i] > v;
					}
				}
			}
			upmax(ans, tmp);
			tmp = 0;
			rep (i, 1, n-1) {
				if (Y[i - 1] <= v) {
					tmp += Y[i] > v;
				} else {
					tmp += Y[i] <= v;
				}
			}
			upmax(ans, tmp);
		}
		return ans;
	}
};
