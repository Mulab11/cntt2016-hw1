#line 2 "KingdomAndCities.cpp"
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
#define mo 1000000007
#define oo 0x3f3f3f3f
#define maxn 60
typedef long long ll;
using namespace std;
int c[maxn * maxn][maxn], f[maxn][maxn], g[maxn][maxn], all[maxn][maxn]; // c是组合数，all[i][j]表示i个点j条边的无向简单图总数，f[i][j]表示i个点j条边的无向简单联通图个数，g = all - f，
void add(int &a, int b) {
	a += b; a %= mo;
}
class KingdomAndCities {
	public:
		int howMany(int N, int M, int K) {
			cl(c); cl(f); cl(g); cl(all);
			for (int i = 0; i <= N * N; ++i) { // 处理组合数
				c[i][0] = 1;
				for (int j = 1; j <= min(i, max(N, K)); ++ j)
					c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mo;
			}
			for (int i = 0; i <= N; ++i)
				for (int j = 0; j <= K; ++j)
					all[i][j] = c[c[i][2]][j];
			for (int i = 0; i <= N; ++i)
				for (int j = 0; j <= K; ++j) {
					g[i][j] = 0;
					for (int k = 1; k < i; ++k)
						for (int p = 0; p <= j; ++p) // 容斥计算g
							add(g[i][j], 1ll * f[k][p] * c[i - 1][k - 1] % mo * all[i - k][j - p] % mo);
					f[i][j] = (all[i][j] + mo - g[i][j]) % mo;
				}
			if (M == 0) return f[N][K];
			if (M == 1) {
				int ans = 1ll * f[N - 1][K - 1] * (K - 1) % mo; // 0号点插到一条边的中间
				add(ans, 1ll * f[N - 1][K - 2] * (K - 2) % mo); // 0号点连着一对边，一起并到一条边的两端
				return ans;
			}
			if (M == 2) {
				int ans = 0;
				if (K >= 2) add(ans, 1ll * f[N - 2][K - 2] * (K - 2) % mo * (K - 1) % mo); // 0 与 1 均插入到某条已有的边上
				if (K >= 4) add(ans, 2ll * f[N - 2][K - 3] * (K - 3) % mo * (K - 4) % mo); // 0 与 1 中的一个插入到已有的边上，另一个跨越另一条已有的边
				if (K >= 3) add(ans, 1ll * f[N - 2][K - 3] * (K - 3) % mo); // 0 与 1 连接同一对点
				if (K >= 4) add(ans, 1ll * f[N - 2][K - 4] * (K - 4) % mo * (K - 4) % mo); // 0 和 1 都跨越某条已有的边
				if (K >= 3) add(ans, 2ll * f[N - 2][K - 3] * (K - 3) % mo); // 0 和 1 串在一起跨越某条已有的边
				if (K >= 3) add(ans, 1ll * f[N - 2][K - 3] * (N - 2) % mo); // 0 和 1 串在一起和另外一个点成一个三元环
				return ans;
			}
		}
};

