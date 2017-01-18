#line 2 "XorCards.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
typedef long long ll;
using namespace std;
int n, tar[maxn], dig[maxn][maxn];
int a[maxn][maxn], x[maxn];
ll calc(int m, int n) {
	for (int row = 1, i = 1; i <= n && row <= m; ++i, ++row) {
		for (int j = row; j <= m; ++j)
			if (a[j][i]) {
				swap(a[row], a[j]);
				break;
			}
		if (!a[row][i]) {
			--row; continue;
		}
		for (int j = row + 1; j <= m; ++j)
			if (a[j][i]) {
				for (int k = i; k <= n + 1; ++k)
					a[j][k] ^= a[row][k];
			}
	}
	ll ret = (1ll << ll(n));
	for (int i = 1; i <= m; ++i) {
		bool flag = 0;
		for (int j = 1; j <= n; ++j)
			if (a[i][j]) flag = 1;
		if (!flag && a[i][n + 1]) return 0ll;
		if (flag) ret /= 2ll;
	}
	return ret;
}
class XorCards {
	public:
		long long numberOfWays(vector<long long> number, long long limit) {
			n = number.size();
			for (int i = 0; i < n; ++i) 
				for (int j = 0; j < 50; ++j)
					dig[i][j] = bool(number[i] & (1ll << ll(j)));
			for (int j = 0; j < 50; ++j)
				tar[j] = bool(limit & (1ll << ll(j)));
			ll ans = (1ll << ll(n));
			for (int d = 49; d >= 0; --d) {
				if (tar[d] == 1) continue;
				cl(a);
				for (int i = d + 1; i < 50; ++i)
					a[i - d + 1][n + 1] = tar[i];
				a[1][n + 1] = 1;
				for (int i = d; i < 50; ++i)
					for (int j = 0; j < n; ++j)
						a[i - d + 1][j + 1] = dig[j][i];
				ans -= calc(50 - d, n);
			}
			return ans;
		}
};
