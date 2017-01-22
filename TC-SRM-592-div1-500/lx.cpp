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

template<typename T>
inline void read(T &x) {
	char c;
	while ((c = getchar()) < '0' || c > '9');
	for (x = c - '0'; (c = getchar()) >= '0' && c <= '9'; x = x * 10 + c - '0');
}

const int inf = 0x3f3f3f3f;
const int mo = 1e9 + 7;

class LittleElephantAndPermutationDiv1 {
private :
	int f[52][52][2677];
	inline void upd(int &x, int y) {
		(x += y) >= mo ? x -= mo : 0;
	}
public :
	//DP
	int getNumber(int n, int K) {
		int sum = 0;
		f[0][0][0] = 1;
		rep (i, 1, n) {
			rep (j, 0, i-1) {
				rep (k, 0, sum) {
					int x = f[i - 1][j][k];
					upd(f[i][j][k + i], x);
					upd(f[i][j + 1][k], x);
					if (j) {
						x = (LL) x * j % mo;
						upd(f[i][j][k + i], 2 * x % mo);
						x = (LL) x * j % mo;
						upd(f[i][j - 1][k + i + i], x);
					}
				}
			}
			sum += i * 2;
		}
		int ans = 0;
		rep (i, K, sum) upd(ans, f[n][0][i]);
		rep (i, 1, n) ans = (LL) ans * i % mo;
		return ans;
	}
};
