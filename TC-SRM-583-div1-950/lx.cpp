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

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 21;

class RandomPaintingOnABoard {
private :
	int sc[N], tw[N];
	int w[N][N], sum;
	int f[1403];
public :
	double expectedSteps(vector<string> P) {
		int n = P.size(), m = P[0].size();
		if (n <= m) {
			rep (i, 0, n - 1) rep (j, 0, m - 1)
				w[i][j] = P[i][j] - '0';
		} else {
			rep (i, 0, n - 1) rep (j, 0, m - 1)
				w[j][i] = P[i][j] - '0';
			swap(n, m);
		}
		rep (i, 0, n - 1) rep (j, 0, m - 1) {
			sum += w[i][j];
			sc[j] += w[i][j];
		}
		double ans = 0.0;
		rep (s, 0, bin(n) - 1) {
			int c = 0, s1 = 0, s2 = 0;
			fill(tw, tw + m, 0);
			rep (i, 0, n - 1) {
				if (s & bin(i)) {
					rep (j, 0, m - 1) {
						tw[j] += w[i][j];
					}
					++c;
				}
			}
			rep (i, 0, m - 1)  s1 += tw[i];
			s2 = sum - s1;
			fill(f, f + s2 + 1, 0);
			f[0] = 1;
			rep (j, 0, m - 1) {
				int q = sc[j] - tw[j];
				down (v, s2 - q, 0) {
					f[v + q] -= f[v];
				}
			}
			double tmp = 0.0;
			rep (i, 0, s2) if (s1 + i) {
				tmp += (double) sum / (s1 + i) * f[i];
			}
			c & 1 ? ans += tmp : ans -= tmp;
		}
		return ans;
	}
};
