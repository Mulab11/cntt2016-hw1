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

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class EelAndRabbit {
public :
	int getmax(vector<int> len, vector<int> tim) {
		int n = len.size();
		set<int> chose;
		rep (i, 0, n - 1) {
			chose.insert(tim[i]);
			chose.insert(tim[i] + len[i]);
		}
		int ans = 0;
		for (int p : chose) {
			for (int q : chose) {
				if (q >= p)  continue ;
				int tmp = 0;
				rep (i, 0, n - 1) {
					if (tim[i] <= p && p <= tim[i] + len[i])
						++tmp;
					else if (tim[i] <= q && q <= tim[i] + len[i])
						++tmp;
				}
				upmax(ans, tmp);
			}
		}
		return ans;
	}
};
