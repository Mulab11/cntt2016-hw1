#line 2 "SemiPerfectPower.cpp"
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
#define maxn 500010
#define div divv
#define eps 1e-12
typedef long long ll;
using namespace std;
int F[maxn * 10], l[maxn], len[maxn]; // F[]用来存储g(d * k, d), l[d]标记g(d * k, d)在F中下标的开始位置。len[d]表示g(d * k, d)在F中占的长度
int div[maxn][10]; // div[i][]记录i的质因子
bool sf[maxn], cf[maxn]; // sf[i] = 1 <==> i是square-free数。cf[i] = 1 <==> i是cube-free数
inline int g(int n, int a) { // 不超过n且是a的倍数的square-free数，g(n, a) = g((n / a) * a, a). 在F[l[a] + k]中存储g(a * k, a)
	return n < a ? 0 : F[l[a] + n / a];
}
inline int f(int n, int a) { // 不超过n且与a互质的square-free数
	if (!n) return 0;
	int tot = div[a][0], ret = 0;
	for (int s = 0; s < (1 << tot); ++s) { // 容斥
		int cnt = 0, x = 1;
		for (int i = 0; i < tot; ++i)
			if (s & (1 << i))
				++cnt, x *= div[a][i + 1];
		if (cnt & 1)
			ret -= g(n, x);
		else
			ret += g(n, x);
	}
	return ret;
}
void pre(int n) {
	for (int i = 1; i <= n; ++i) sf[i] = cf[i] = 1;
	for (int i = 2; i * i <= n; ++i) 
		for (int j = 1; 1ll * i * i * j <= n; ++j) 
			sf[i * i * j] = 0; // 标记有square因子的数
	for (int i = 2; i * i * i <= n; ++i)
		for (int j = 1; 1ll * i * i * i * j <= n; ++j)
			cf[i * i * i * j] = 0; // 标记有cube因子的数
	for (int i = 1; i <= n; ++i)
		if (sf[i]) { // 分解square-free的i的质因子
			int tmp = i; div[i][0] = 0;
			for (int j = 2; 1ll * j * j <= tmp; ++j)
				if (tmp % j == 0) {
					div[i][++div[i][0]] = j;
					tmp /= j;
				}
			if (tmp > 1)
				div[i][++div[i][0]] = tmp;
		}
	for (int i = 1; i <= n; ++i) {
		l[i] = l[i - 1] + len[i - 1]; 
		if (!sf[i]) {
			len[i] = 0; continue;
		}
		len[i] = n / i; // g(x, i) = g((x / i) * i, i), 只要记录g(k * i, i)的值，k = 1 ... n / i,所以需要(n / i)个位置
		F[l[i] + 1] = sf[i];
		for (int j = 2; j <= len[i]; ++j)
			F[l[i] + j] = F[l[i] + j - 1] + sf[j * i]; // g(j * i, i)
	}
}
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
ll sqrt(ll x) { // 卡精度
	ll l = 0, r = 1e9, mid, ret;
	while (l <= r) {
		mid = (l + r) >> 1ll;
		if (mid * mid <= x) {
			ret = mid; l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return ret;
}
ll cbrt(ll x) { // 卡精度
	ll l = 0, r = 1e6, mid, ret;
	while (l <= r) {
		mid = (l + r) >> 1ll;
		if (mid * mid * mid <= x) {
			ret = mid; l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return ret;
}
ll calc(ll n) {
	ll ans = 0;
	ll lim = ll(pow(n, 1.0 / 3.0) + eps);
	for (ll i = 1; i <= lim; ++i)
		if (sf[i])
			ans += sqrt(n / i) - i; // p = i * b * b, b \in [i + 1, sqrt(n / i)]
	lim = ll(pow(n, 1.0 / 4.0) + eps);
	for (ll x = 1; x <= lim; ++x) { // 枚举p = x * y * y * y = a * b * b, 其中a >= b且(a, b) = 1
		if (!cf[x]) continue;
		for (ll k = 1; k * k * k <= x; ++k) {
			ll a = x / gcd(x, k * k), y = k * k / gcd(x, k * k);
			if (!sf[a]) continue;
			ll lim = cbrt(n / x) / y;
			if (lim <= x / y) continue;
			ans += max(0, f(lim, a) - f(x / y, a)); // p -> pQ^3 = x(yQ) ^ 3 = aQ(bQ) ^ 2, Q要满足pQ^3 <= n且x < yQ, 且Q是square-free的，与a互质
		}
	}
	return ans;
}
class SemiPerfectPower {
	public:
		long long count(long long L, long long R) {
			pre(500000);
			return calc(R) - calc(L - 1);
		}
};
