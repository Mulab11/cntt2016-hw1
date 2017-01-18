#line 2 "Excavations.cpp"
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
#define find findd
typedef long long ll;
using namespace std;
/*
   一个建筑集合是合法的，需要存在一个D，满足对于每类能被发现的建筑，至少有一个depth <= D且被选中挖掘的建筑。即D >= max{每类能被发现的建筑中，被选中的建筑的最小depth}.对于每类未被发现的建筑，min{被选中的建筑的depth} > D. 即max{每类能被发现的建筑中，被选中的建筑的最小depth} < min{未被发现且被选中的建筑的depth}
   dp出两种建筑挖掘i个，最大值/最小值为j的方案数，选择i1 + i2 = K, j1 < j2的方案的乘积累入答案。
*/
int n, m, pos[maxn]; // n, m分别是被发现的/没被发现的建筑种数，pos[i]标记第i种建筑在它所在类别中排在的顺序
bool find[maxn]; // find[i]标记第i种建筑是否被发现
vector<int> a[maxn], b[maxn]; // a[], b[]分别存被发现的/没被发现的每种建筑的不同深度
ll f[maxn][maxn][maxn], g[maxn][maxn][maxn], C[maxn][maxn]; // f[i][j][k]表示考虑被发现的n种建筑中的前i种，选择j个挖掘，选中的建筑中，每类的最浅深度的最大值为k，的方案数。g[i][j][k]表示考虑没被发现的m种建筑中的前i种，选择j个挖掘，选中的建筑中，每类的最浅深度的最小值为k，的方案数。C[][]是组合数
int val[maxn], vt; // 离散化depth
void dp(int n, vector<int> a[maxn], ll f[maxn][maxn][maxn], bool must) { // n是建筑种数，a[]存每种建筑的各种depth，f是dp数组，must=1表示这里考虑能被发现的建筑
	for (int i = 1; i <= n; ++i)
		sort(a[i].begin(), a[i].end());
	f[0][0][must ? 0 : vt + 1] = 1ll;
	int sum = 0;
	for (int i = 1; i <= n; ++i) { // 考虑前i种建筑
		int sz = a[i].size();
		for (int j = 0; j <= sum; ++j) // 此前使用的挖掘次数
			for (int k = 0; k <= vt + 1; ++k) { // 此前的最大/最小值
				if (!must)
					f[i][j][k] += f[i - 1][j][k]; // 不挖掘这种建筑
				for (int p = 1; p <= sz; ++p) { // 枚举挖掘的这种建筑中，最浅的一个
					int nk = must ? max(k, a[i][p - 1]) : min(k, a[i][p - 1]);
					for (int q = 1; q <= sz - p + 1; ++q) // 枚举挖掘的这种建筑的总数
						f[i][j + q][nk] += f[i - 1][j][k] * C[sz - p][q - 1]; // 后面的q - 1个不影响状态，用组合数算
				}
			}
		sum += sz;
	}
}
class Excavations {
	public:
		long long count(vector <int> kind, vector <int> depth, vector <int> found, int K) {
			for (int i = 0; i <= 50; ++i) {
				C[i][0] = 1ll;
				for (int j = 1; j <= i; ++j)
					C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			}
			cl(find); cl(f); cl(g);
			for (int i = 0; i < found.size(); ++i)
				find[found[i]] = 1; // 标记能被找到的建筑种类
			n = 0; m = 0;
			for (int i = 1; i <= 50; ++i)
				if (find[i]) 
					pos[i] = ++n, a[n].clear(); // 给建筑种类安排位置
				else
					pos[i] = ++m, b[m].clear();
			vt = 0;
			for (int i = 0; i < depth.size(); ++i)
				val[++vt] = depth[i];
			sort(val + 1, val + vt + 1);
			vt = unique(val + 1, val + vt + 1) - val - 1; 
			for (int i = 0; i < depth.size(); ++i)
				depth[i] = lower_bound(val + 1, val + vt + 1, depth[i]) - val; // 离散化depth
			for (int i = 0; i < kind.size(); ++i)
				if (find[kind[i]])
					a[pos[kind[i]]].pb(depth[i]);
				else
					b[pos[kind[i]]].pb(depth[i]);
			dp(n, a, f, 1);
			dp(m, b, g, 0);
			ll ans = 0;
			for (int i = n; i <= K; ++i)
				for (int j = 0; j <= vt + 1; ++j)
					if (f[n][i][j])
						for (int k = j + 1; k <= vt + 1; ++k)
							ans += f[n][i][j] * g[m][K - i][k]; // 能被挖到的depth最大值 < 不能被挖到的depth最小值
			return ans;
		}
};
