#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define SZ(x) ((x).size())
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

template<typename T>
inline void read(T & x) {
	char c;
	while ((c = getchar()) < '0' || c > '9');
	for (x = c - '0'; (c = getchar()) >= '0' && c <= '9'; x = x * 10 + c - '0');
}

const int inf = 0x3f3f3f3f;
const int N = 51;

#define bin(x) (1<<(x))

class TravellingPurchasingMan {
public :
	int obj[17][3], n, m;
	int d[N][N], f[bin(16)|1][N];

	int maxStores(int n, vector<string> stores, vector<string> roads) {
		this->n = n;
		this->m = SZ(stores);
		stringstream ss;
		rep (i, 0, m - 1) {
			ss.clear();
			ss << stores[i];
			rep (j, 0, 2)  ss >> obj[i][j];
		}
		memset(d, 0x3f, sizeof(d));
		rep (i, 0, n - 1)  d[i][i] = 0;
		rep (i, 0, SZ(roads) - 1) {
			ss.clear();
			ss << roads[i];
			int x, y, z;
			ss >> x >> y >> z;
			d[x][y] = d[y][x] = z;
		}
		rep (k, 0, n - 1) {
			rep (i, 0, n - 1) rep (j, 0, n - 1)
				upmin(d[i][j], d[i][k] + d[k][j]);
		}
		memset(f, 0x3f, sizeof(f));
		rep (i, 0, m - 1) {
			int x = d[n - 1][i];
			if (x <= obj[i][1]) {
				f[bin(i)][i] = max(x, obj[i][0]) + obj[i][2];
			}
		}
		rep (s, 1, bin(m) - 1) {
			rep (i, 0, m - 1) if (f[s][i] < inf) {
				int x = f[s][i];
				rep (j, 0, m - 1) {
					if (!(s & bin(j)) && x + d[i][j] <= obj[j][1]) {
						upmin(f[s ^ bin(j)][j], max(x + d[i][j], obj[j][0]) + obj[j][2]);
					}
				}
			}
		}
		int ans = 0;
		rep (s, 1, bin(m) - 1) {
			int c = 0;
			for (int i = s; i; i -= i & -i)  ++c;
			if (c > ans) {
				rep (i, 0, m - 1) {
					if (f[s][i] < inf) {
						ans = c;
						break ;
					}
				}
			}
		}
		return ans;
	}
};
