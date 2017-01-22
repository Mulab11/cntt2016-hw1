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
const int N = 2505;

class LittleElephantAndRGB {
private :
	char str[N];
	int n, m;

	inline int sum1(int x) {
		return x * (x - 1) / 2;
	}
	inline int calc(int a, int b, int x, int y) {
		if (a + x < m)  return 0;
		int res = b * y;
		if (a + x - m > 0) {
			res += min(a + x - m, x - 1) * b;
			res += min(a + x - m, a - 1) * y;
			res += sum1(a + x - m);
		}
		return res;
	}
public :
	LL getNumber(vector<string> &list, int m) {
		this->m = m;
		rep (i, 0, list.size()-1) {
			rep (j, 0, list[i].size()-1) {
				str[n++] = list[i][j];
			}
		}
		LL ans = 0;
		int lp = -1, ld = 0, cnt = 0;
		rep (i, 0, n-1) {
			ld = str[i] == 'G' ? ld + 1 : 0;
			if (ld == m) {
				ld = m - 1;
				lp = i - m + 1;
				cnt = lp + 1;
			}
			ans += (LL) cnt * sum1(n - i);
			int d = 0, p = n, c = 0;
			down (j, n-1, i+1) {
				d = str[j] == 'G' ? d + 1 : 0;
				if (d == m) {
					d = m - 1;
					p = j + m - 1;
					c = n - p;
				}
				ans += c * (i - lp);
				ans += calc(ld, i-ld-lp+1, d, p-j-d+1);
			}
		}
		return ans;
	}
};
