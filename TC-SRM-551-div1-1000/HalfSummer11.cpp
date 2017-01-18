#line 2 "SweetFruits.cpp"
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
#define mo 1000000007
#define maxn 50
typedef long long ll;
using namespace std;
int n, m, k, val[maxn]; // n是点的总数，m是正点的个数，k是-1点的个数，val存所有正点的权值
vector <int> sum[maxn]; // 在mim时，sum[num]存前半段选出num个点，所得到的各种权值和
int a[maxn][maxn]; // 存度数矩阵 - 邻接矩阵，用来求生成树个数
int f[maxn], g[maxn], cnt[maxn];
// f[x]是只与-1相邻的正点恰为集合S时，且集合S的大小为x时，生成树的个数
// g[x]是S中的点只与-1相邻，别的点不一定，且集合S的大小为x时，生成树的个数
// cnt[x]是大小为x，且权值和至少为total - lim的集合的总数
int c[maxn][maxn]; // 组合数
void add(int &a, int b) { // 给a加上b
	a += b; a %= mo;
}
int power(int a, int b) { // 计算a ^ b
	int c = 1;
	for ( ; b; b >>= 1, a = 1ll * a * a % mo)
		if (b & 1) c = 1ll * c * a % mo;
	return c;
}
int det(int n) { // 算行列式
	int ret = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j)
			if (a[j][i]) {
				swap(a[i], a[j]); 
				break;
			}
		if (!a[i][i]) return 0;
		int inv = power(a[i][i], mo - 2);
		for (int j = i + 1; j <= n; ++j) {
			int t = 1ll * a[j][i] * inv % mo;
			for (int k = i; k <= n; ++k)
				add(a[j][k], mo - 1ll * t * a[i][k] % mo);
		}
		ret = 1ll * ret * a[i][i] % mo;
	}
	return ret;
}
class SweetFruits {
	public:
		int countTrees(vector <int> sweet, int lim) {
			n = sweet.size(); m = 0; k = 0; cl(cnt);
			lim = -lim; // 把题目条件转化为，只与-1相邻的正点的权值和至少为total - lim
			for (int i = 0; i < n; ++i) 
				if (sweet[i] == -1) 
					++ k;
				else 
					val[++m] = sweet[i], lim += sweet[i];
			int half = m / 2; // mim来求cnt
			for (int i = 0; i <= half; ++i) sum[i].clear();
			for (int s = 0; s < (1 << half); ++s) { // 枚举前半段中选择的点，根据选出点的个数，把这些点的权值和存入sum
				int num = 0, tot = 0;
				for (int i = 0; i < half; ++i)
					if (s & (1 << i)) {
						++num; tot += val[i + 1];
					}
				sum[num].pb(tot);
			}
			for (int i = 0; i <= half; ++i) 
				sort(sum[i].begin(), sum[i].end()); // 排序，便于之后寻找“前半段中选出i个，且其权值和至少为xxx”的方案数
			int rest = m - half;
			for (int s = 0; s < (1 << rest); ++s) { // 枚举后半段选出的点
				int num = 0, tot = 0;
				for (int i = 0; i < rest; ++i)
					if (s & (1 << i)) {
						++num; tot += val[half + i + 1];
					}
				for (int i = 0; i <= half; ++i) // 枚举前半段选出的点数，算出其中满足条件的集合个数
					add(cnt[i + num], sum[i].size() - (lower_bound(sum[i].begin(), sum[i].end(), lim - tot) - sum[i].begin()));
			}
			for (int num = 0; num <= m; ++num) { // 枚举只与-1相邻的点的个数num，造矩阵
				for (int i = 1; i <= n; ++i)
					for (int j = 1; j <= n; ++j)
						a[i][j] = -(i != j);
				for (int i = k + 1; i <= k + num; ++i)
					for (int j = k + 1; j <= n; ++j)
						a[i][j] = a[j][i] = 0; // 编号为1-k的点为-1点，k+1-k+num的为只与-1相邻的点，k+num+1-n的为普通点。这里去掉只与-1相邻的点和别的点之间的连边
				for (int i = 1; i <= k; ++i) a[i][i] += n - 1;
				for (int i = k + 1; i <= k + num; ++i) a[i][i] += k;
				for (int i = k + num + 1; i <= n; ++i) a[i][i] += n - num - 1;
				g[num] = det(n - 1); // 计算生成树个数
			}
			for (int i = 0; i <= n; ++i) { // 处理组合数
				c[i][0] = 1;
				for (int j = 1; j <= i; ++j)
					c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
			}
			for (int num = 0; num <= m; ++num) { 
				f[num] = 0;
				for (int i = num; i <= m; ++i) { // 容斥计算f
					int tmp = 1ll * g[i] * c[m - num][m - i] % mo;
					if ((i - num) & 1)
						add(f[num], mo - tmp);
					else
						add(f[num], tmp);
				}
			}
			int ans = 0;
			for (int num = 0; num <= m; ++num)
				add(ans, 1ll * f[num] * cnt[num] % mo);
			return ans;
		}
		
};

