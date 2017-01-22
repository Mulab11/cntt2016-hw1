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

const int N = 53;

class Excavations {
private :
	vector<int> hav[N];
	int vis[N], n, m;
	LL C[N][N], f[N][N];
public :
	LL count(vector<int> kind, vector<int> dep, vector<int> found, int K) {
		n = kind.size();
		rep (i, 0, found.size() - 1) {
			vis[found[i]] = ++m;
		}
		rep (i, 0, n - 1) {
			hav[vis[kind[i]]].pb(dep[i]);
		}
		sort(hav[0].begin(), hav[0].end());
		C[0][0] = 1;
		rep (i, 1, n) {
			C[i][0] = 1;
			rep (j, 1, i)
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
		LL ans = 0;
		int ct = hav[0].size();
		rep (i, 0, ct) {
			int v = i < ct ? hav[0][i] : 100005;
			memset(f, 0, sizeof(f));
			f[0][max(ct - i - 1, 0)] = 1;
			rep (j, 1, m) {
				int a = 0, b = hav[j].size();
				rep (k, 0, b - 1) {
					a += (hav[j][k] >= v);
				}
				if (a == b)  break ;
				LL sum = 0;
				rep (k, 0, n) {
					if (k >= a)  sum += f[j - 1][k - a];
					if (k >= b)  sum -= f[j - 1][k - b];
					f[j][k] += sum;
				}
			}
			int ut = K - (m + (i < ct));
			rep (j, ut, n) {
				ans += f[m][j] * C[j][ut];
			}
		}
		return ans;
	}
};
