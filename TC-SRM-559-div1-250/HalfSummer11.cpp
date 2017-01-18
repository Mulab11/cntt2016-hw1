#line 2 "HyperKnight.cpp"
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
#define maxn 10
typedef long long ll;
using namespace std;
int l[maxn], r[maxn], u[maxn], d[maxn]; // l,r,u,d[i]表示能进行第i个move的格子所在的坐标范围
ll f[1 << 8]; // f[s]表示只能进行s中的move的格子的个数
class HyperKnight {
	public:
		long long countCells(int a, int b, int n, int m, int k) {
			for (int i = 0; i < 8; ++i)
				l[i] = 1, r[i] = n, d[i] = 1, u[i] = m;
			l[0] += a; l[1] += b; l[2] += a; l[3] += b; // 处理能进行每种move的格子所在的坐标范围
			r[4] -= a; r[5] -= b; r[6] -= a; r[7] -= b;
			d[0] += b; d[1] += a; u[2] -= b; u[3] -= a;
			d[4] += b; d[5] += a; u[6] -= b; u[7] -= a;
			ll ans = 0;
			for (int s = 0; s < (1 << 8); ++s) {
				int L = 1, R = n, D = 1, U = m;
				for (int i = 0; i < 8; ++i)
					if (s & (1 << i)) {
						L = max(L, l[i]); D = max(D, d[i]); // 坐标范围取交
						R = min(R, r[i]); U = min(U, u[i]);
					}
				f[s] = 1ll * (R - L + 1) * (U - D + 1); // 目前f[s]的意义是可以进行s中的move的格子的个数
			}
			for (int s = (1 << 8) - 1; s >= 0; --s) {
				for (int t = (s - 1) & s; ; t = (t - 1) & s) { // 容斥，去掉不止能进行s中的move的格子
					f[t] -= f[s];
					if (!t) break;
				}
				if (__builtin_popcount(s) == k) ans += f[s]; // 若只能进行k个move，累入答案
			}
			return ans;
		}
};
