#line 2 "GearsDiv1.cpp"
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
int n, m, G[maxn][maxn];
int link[maxn]; 
bool vis[maxn];
bool dfs(int x) {
	for (int i = 1; i <= m; ++i)
		if (G[x][i] && !vis[i]) {
			vis[i] = 1;
			if (!link[i] || dfs(link[i])) {
				link[i] = x;
				return 1;
			}
		}
	return 0;
}
int calc() {
	cl(link);
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		cl(vis); 
		if (dfs(i)) ++ret;
	}
	return ret;
}
class GearsDiv1 {
	public:
		int getmin(string color, vector <string> graph) {
			int len = color.size();
			int num[maxn];
			int ans = oo;
			for (int o = 0; o <= 2; ++o) {
				char c1, c2;
				if (o == 0) c1 = 'R', c2 = 'G';
				if (o == 1) c1 = 'R', c2 = 'B';
				if (o == 2) c1 = 'G', c2 = 'B';
				n = m = 0; cl(num);
				for (int i = 0; i < len; ++i) {
					if (color[i] == c1) num[i] = ++n;
					if (color[i] == c2) num[i] = ++m;
				}
				cl(G);
				for (int i = 0; i < len; ++i)
					if (color[i] == c1)
						for (int j = 0; j < len; ++j)
							if (color[j] == c2)
								if (graph[i][j] == 'Y')
									G[num[i]][num[j]] = 1;
				ans = min(ans, calc());
			}
			return ans;
		}
};
