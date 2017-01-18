#line 2 "PenguinEmperor.cpp"
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
#define maxn 400
#define mo 1000000007
typedef long long ll;
using namespace std;
// 在模n意义下,第i天与第(kn + i)天的移动是一样的.可以把天数按照n划分成若干段,每个完整的(kn + 1) ... (kn + n)的情况,用dp先计算
// 然后,这些段的答案卷起来就是答案了
int f[maxn][maxn]; // f[i][j]表示i天后,penguin在城市j,不同的路径数
int a[maxn], ans[maxn], tmp[maxn]; 
void add(int &a, int b) {
	a += b; a %= mo;
}
void conv(int n, int a[maxn], int b[maxn], int c[maxn]) { // 把a和b的循环卷积放到c里
	for (int i = 0; i < n; ++i) c[i] = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			add(c[(i + j) % n], 1ll * a[i] * b[j] % mo); // 卷
}
void power(int n, ll len) { // 快速幂计算a的len次卷积
	cl(ans); ans[0] = 1;
	for (; len; len >>= 1ll) {
		if (len & 1ll) {
			conv(n, ans, a, tmp);
			for (int i = 0; i < n; ++i) ans[i] = tmp[i];
		}
		conv(n, a, a, tmp);
		for (int i = 0; i < n; ++i) a[i] = tmp[i];
	}
}
class PenguinEmperor {
	public:
		int countJourneys(int n, long long d) {
			cl(f); f[0][0] = 1;
			for (int i = 1; i <= n; ++i) // 枚举第(kn + i)天的移动方向
				for (int j = 0; j < n; ++j) {
					add(f[i][(j + i) % n], f[i - 1][j]);
					if (i * 2 != n && i != n) // 注意是按照城市的不同来判断路径的不同,如果往两个方向走到了同一个城市,只能计算一次
						add(f[i][(j + n - i) % n], f[i - 1][j]);
				}
			ll len = d / (ll)n; int rest = d % (ll)n;
			for (int i = 0; i < n; ++i) a[i] = f[n][i];
			power(n, len); // 将这完整的len段的内容卷起来
			conv(n, ans, f[rest], tmp); // 和剩下的长度为rest的这段相卷
			return tmp[0];
		}
};
