#line 2 "LISNumber.cpp"
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
#define maxn 1300
#define mo 1000000007
typedef long long ll;
using namespace std;
int n, sum, c[maxn][maxn]; // n是数字种数，sum是数字总数，c[i][j]是组合数
int g[maxn], f[maxn], r[maxn]; // g[i]表示把数字分到K个有序严格递增序列中的方案数，f[i]表示把数字分到K个有序非空严格递增序列中的方案数，r[i]表示LISNumber = i的序列个数
vector<int> cnt; // 数字
int calc(int K) { // 计算g[K]
	if (K < 0) return 0;
	int ans = 1;
	for (int i = 0; i < n; ++i)
		ans = 1ll * ans * c[K][cnt[i]] % mo; // 从小到大放数字，只要保证同样大的数字位于不同的序列中即可
	return ans;
}
class LISNumber {
	public:
		int count(vector <int> Cnt, int K) {
			cnt = Cnt;
			n = cnt.size(); sum = 0;
			for (int i = 0; i < n; ++i)
				sum += cnt[i];
			for (int i = 0; i <= max(sum, K); ++i) {
				c[i][0] = 1;
				for (int j = 1; j <= i; ++j)
					c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
			}
			for (int i = 1; i <= K; ++i) g[i] = calc(i);
			for (int i = 1; i <= K; ++i) {
				f[i] = g[i];
				for (int j = 1; j < i; ++j)
					f[i] = (f[i] - 1ll * f[j] * c[i][i - j] % mo + mo) % mo; // 枚举实际上非空的序列个数j，去掉它的影响
			}
			if (sum < K) return 0; // 无解
			for (int i = 1; i <= K; ++i) {
				r[i] = f[i];
				for (int j = 1; j < i; ++j)
					r[i] = (r[i] + mo - 1ll * c[sum - j][i - j] * r[j] % mo) % mo; // 考虑实际上LISNumber = j的序列对f[i]的贡献，它共有sum - j个位置可以割开，从中选择i - j个的方案数就是它对f[i]的贡献
			}
			return r[K];
		}
};
