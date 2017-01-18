#line 2 "BitwiseAnd.cpp"
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
#define maxn 70
typedef long long ll;
using namespace std;
ll a[maxn], used[maxn];
class BitwiseAnd {
	public:
		vector<long long> lexSmallest(vector<long long> subset, int n) {
			int m = subset.size();
			vector <ll> ans;
			for (int i = 0; i < m; ++i) a[i + 1] = subset[i];
			sort(a + 1, a + m + 1);
			for (int i = 1; i <= m; ++i) {
				for (int j = i + 1; j <= m; ++j) {
					if (a[i] == a[j]) return ans;
					if (!(a[i] & a[j])) return ans;
					for (int k = j + 1; k <= m; ++k)
						if (a[i] & a[j] & a[k]) return ans;
				}
			}
			cl(used);
			for (int i = 1; i <= m; ++i)
				for (int k = 0; k < 60; ++k)
					if (a[i] & (1ll << ll(k)))
						++used[k];
			for (int i = m + 1; i <= n; ++i) {
				ll now = 0ll;
				for (int j = 1; j < i; ++j) {
					bool flag = 0;
					for (int k = 0; k < 60; ++k)
						if (used[k] < 2 && (a[j] & (1ll << ll(k)))) {
							now += (1ll << ll(k));
							used[k]++;
							flag = 1;
							break;
						}
					if (!flag) return ans;
				}
				int need = (n - i);
				for (int k = 0; need && k < 60; ++k)
					if (used[k] == 0) {
						--need;
						now += (1ll << ll(k));
						++used[k];
					}
				if (need) return ans;
				a[i] = now;
			}
			sort(a + 1, a + n + 1);
			for (int i = 1; i <= n; ++i)
				ans.pb(a[i]);
			return ans;
		}
};
