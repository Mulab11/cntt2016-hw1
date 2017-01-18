#line 2 "Incubator.cpp"
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
int n, link[maxn]; // link[i]表示与Y部第i个点匹配的X部点的标号
bool g[maxn][maxn], vis[maxn];
bool find(int x) { // 寻找从x开始的增广路
	for (int y = 1; y <= n; ++y)
		if (!vis[y] && g[x][y]) {
			vis[y] = 1;
			if (!link[y] || find(link[y])) {
				link[y] = x; return 1;
			}
		}
	return 0;
}
class Incubator {
	public:
		int maxMagicalGirls(vector <string> love) {
			n = love.size(); cl(g);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (love[i][j] == 'Y')
						g[i + 1][j + 1] = 1;
			for (int k = 1; k <= n; ++k) // 传递闭包
				for (int i = 1; i <= n; ++i)
					for (int j = 1; j <= n; ++j)
						g[i][j] |= (g[i][k] & g[k][j]);
			cl(link);
			int ans = n; // 求DAG的最长反链 = 最小链覆盖 = n - 最大匹配
			for (int i = 1; i <= n; ++i) {
				cl(vis);
				if (find(i)) --ans;
			}
			return ans;
		}
};
