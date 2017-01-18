#line 2 "SpaceWarDiv1.cpp"
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
int n, m, a[maxn], b[maxn]; // n是magical girl个数，m是enemy种数。a[], b[]分别存g和e的strength
int tmp[maxn];
ll c[maxn], d[maxn]; // c[i]是第i种enemy的人数，d[i]是第i个girl的fatigue值
bool cmp(const int &x, const int &y) {
	return b[x] > b[y];
}
bool check(ll lim) { // 是否可能使每个girl的fatigue值均不超过lim
	int j = 1; cl(d); // j是当前的girl编号。
	for (int i = 1; i <= m; ++i) { // 从大到小安排enemy
		ll now = c[tmp[i]];
		while (now) {
			if (j > n || a[j] < b[tmp[i]]) return 0; // 无处可安排
			ll t = lim - d[j]; // 当前girl能打败的enemy数
			if (t <= now) {
				d[j] += t; ++j; now -= t; // 继续塞给下一个girl
			} else {
				d[j] += now; now = 0;
			}
		}
	}
	return 1;
}
class SpaceWarDiv1 {
	public:
		long long minimalFatigue(vector <int> A, vector <int> B, vector<long long> C) {
			n = A.size();
			for (int i = 0; i < n; ++i) a[i + 1] = A[i];
			sort(a + 1, a + n + 1, greater<int>()); // 将girl按照strength从大到小排
			m = B.size();
			for (int i = 0; i < m; ++i) {
				b[i + 1] = B[i];
				c[i + 1] = C[i];
				tmp[i + 1] = i + 1;
			}
			sort(tmp + 1, tmp + m + 1, cmp); // 将enemy也按照strength从大到小排
			ll L = 0, R = 2000000000000000000ll, mid, ans = -1;
			while (L <= R) { // 二分答案
				mid = (L + R) >> 1ll;
				if (check(mid)) {
					ans = mid; R = mid - 1;
				} else {
					L = mid + 1;
				}
			}
			return ans;
		}
};
