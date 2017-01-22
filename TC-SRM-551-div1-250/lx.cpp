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

class ColorfulChocolates {
public :
	//大枚举术
	int maximumSpread(string coc, int M) {
		int ans = 1;
		int n = coc.size();
		rep (k, 0, n-1) {
			int cost = 0, c1 = 0;
			down (i, k, 0) if (coc[i] == coc[k]) {
				cost += k - i - c1;
				c1++;
				int tmp = cost, c2 = 0;
				rep (j, k+1, n-1) if (coc[j] == coc[k]) {
					c2++;
					cost += j - k - c2;
					if (cost <= M) {
						upmax(ans, c1 + c2);
					}
				}
				cost = tmp;
			}
		}
		return ans;
	}
};
