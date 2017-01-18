#line 2 "WolfPack.cpp"
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
#define maxn 100010
#define mo 1000000007
typedef long long ll;
using namespace std;
/*
 	将坐标系旋转45°。如此，纵横坐标上的移动就相互独立了。
	对于一个终点(x, y),可以单独算出所有点在横坐标一维到达它的方案数cntx(x)，在纵坐标一维到达它的方案数cnty(y)，然后相乘。
	答案是一个矩形里的点的方案数之和.根据乘法分配律，将cntx()的和与cnty()的和相乘就是答案。
*/
int n, a[maxn][2], sum[2]; // n是点数，a[i][]存变换后第i个点的两维坐标，sum[]存两维的cnt()和
int fra[maxn], ifr[maxn]; // fra[i] = i!, ifr[i] = 1 / i!
int C(int n, int m) { // 组合数
	if (n < m) return 0;
	return 1ll * fra[n] * ifr[m] % mo * ifr[n - m] % mo;
}
class WolfPack {
	public:
		int calc(vector <int> x, vector <int> y, int m) {
			fra[0] = ifr[0] = ifr[1] = 1; // 预处理阶乘和逆元
			for (int i = 2; i <= m; ++i) 
				ifr[i] = (mo - 1ll * (mo / i) * ifr[mo % i] % mo) % mo;
			for (int i = 1; i <= m; ++i) {
				fra[i] = 1ll * fra[i - 1] * i % mo;
				ifr[i] = 1ll * ifr[i - 1] * ifr[i] % mo;
			}
			n = x.size();
			for (int i = 0; i < n; ++i)
				a[i][0] = x[i] + y[i], a[i][1] = x[i] - y[i]; // 把坐标系旋转45°
			for (int o = 0; o <= 1; ++o) { // 分开处理两维
				int r = (a[0][o] % 2 + 2) % 2; // 在m次移动后，坐标的奇偶性是确定的。需要保证所有起点的坐标奇偶性相同。
				for (int i = 1; i < n; ++i)
					if (abs(a[i][o]) % 2 != r) return 0; // 否则无解
				int L = -oo, R = oo; // L, R是这一维坐标的可达范围
				for (int i = 0; i < n; ++i) {
					L = max(L, a[i][o] - m); // 将每个点的可达范围取交
					R = min(R, a[i][o] + m);
				}
				sum[o] = 0;
				for (int i = L; i <= R; i += 2) { // 枚举可达范围内的每一个坐标
					int now = 1;
					for (int j = 0; j < n; ++j) 
						now = 1ll * now * C(m, (m - abs(a[j][o] - i)) / 2) % mo; // a[j][o]经过m步到达i的方案数
					sum[o] = (sum[o] + now) % mo;
				}
			}
			return 1ll * sum[0] * sum[1] % mo;
		}
};
