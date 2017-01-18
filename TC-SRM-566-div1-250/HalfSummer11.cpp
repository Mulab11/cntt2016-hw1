#line 2 "PenguinSledding.cpp"
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
int deg[maxn], n, m; // n为点数,m为边数,deg[i]是i点的度数
bool g[maxn][maxn]; // 邻接矩阵
class PenguinSledding {
	public:
		long long countDesigns(int n, vector <int> x, vector <int> y) {
			cl(deg); m = x.size(); cl(g);
			if (!m) return 1; // 只能形成一个图,它是合法的
			for (int i = 0; i < m; ++i) {
				++deg[x[i]]; ++deg[y[i]];
				g[x[i]][y[i]] = g[y[i]][x[i]] = 1;
			}
			ll ans = 1 + m; // 一条边都没有的情况 + 只保留一条边的情况
			for (int i = 1; i <= n; ++i) // 保留以i为中心的一个菊花,花瓣需要至少有两个
				ans += (1ll << (ll)deg[i]) - deg[i] - 1;
			for (int i = 1; i <= n; ++i)
				for (int j = i + 1; j <= n; ++j)
					for (int k = j + 1; k <= n; ++k)
						if (g[i][j] && g[j][k] && g[i][k]) ++ans; // 保留三角形ijk
			return ans;
		}
};
