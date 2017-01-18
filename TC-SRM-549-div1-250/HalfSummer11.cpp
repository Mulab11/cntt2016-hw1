#line 2 "PointyWizardHats.cpp"
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
/* 一个二分图匹配题 */
int n, m; // 分别表示top cone和bottom cone的个数
bool g[maxn][maxn]; 
int link[maxn];
bool vis[maxn];
bool find(int x) { // 匈牙利算法
	for (int y = 0; y < m; ++ y)
		if (g[x][y] && ! vis[y]) {
			vis[y] = 1; 
			if (link[y] == -1 || find(link[y])) {
				link[y] = x; return 1;
			}
		}
	return 0;
}
class PointyWizardHats {
	public:
		int getNumHats(vector <int> h1, vector <int> r1, vector <int> h2, vector <int> r2) {
			n = h1.size(); m = h2.size(); cl(g);
			for (int i = 0; i < n; ++ i) 
				for (int j = 0; j < m; ++ j) 
					g[i][j] = (h1[i] * r2[j] > h2[j] * r1[i] && r1[i] < r2[j]); // 判断这对cone能否相配
			memset(link, -1, sizeof(link));
			int ans = 0;
			for (int i = 0; i < n; ++ i) {
				cl(vis);
				if (find(i)) ++ans;
			}
			return ans;
		}
};
