#line 2 "TurnOnLamps.cpp"
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
/*
   将选择一条路径x - y翻转，拆成将1 - x, 1 - y翻转。可以知道每个点最多翻转一次，ceil(翻转的最少点数 / 2)就是答案。
   一条边满足条件，需要它下面的子树里被翻转的点数为奇数/偶数。于是可以树形dp来求。
*/
int n, g[maxn], ei, pre[maxn]; // n是树上的点数，g[], ei是边表,pre[i]存i在树上的父亲
struct edge {
	int t, nxt;
}e[maxn * 2];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
int f[maxn][2], dem[maxn]; // f[i][j]表示，以i为根的子树中所有的边，以及i指向父亲的边，均满足条件，并且以i为根的子树中翻转的点数模2余j，此时翻转点数的最小值。dem[i]表示第i个点连向父亲的边无限制/需要被翻转偶数次/需要被翻转奇数次(-1 / 0 / 1)
void dfs(int x) { // 计算以x为根的子树中的情况
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != pre[x]) {
			pre[e[i].t] = x;
			dfs(e[i].t);
		}
	int g0, g1, f0 = 0, f1 = 1; // g0, g1分别记录目前以x为根子树里选中偶数/奇数个点翻转，且x的所有儿子满足条件，翻转的最小点数。
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != pre[x]) {
			g0 = f0; g1 = f1;
			f0 = oo; f1 = oo;
			f0 = min(f0, g1 + f[e[i].t][1]);
			f0 = min(f0, g0 + f[e[i].t][0]);
			f1 = min(f1, g1 + f[e[i].t][0]);
			f1 = min(f1, g0 + f[e[i].t][1]);
		}
	if (dem[x] != 1) f[x][0] = f0; // 此时，x为根的子树里选偶数个点才是合法的
	if (dem[x] != 0) f[x][1] = f1;
}
class TurnOnLamps {
	public:
		int minimize(vector <int> roads, string initState, string isImportant) {
			cl(g); ei = 0; 
			memset(pre, -1, sizeof(pre));
			memset(dem, -1, sizeof(dem));
			n = roads.size() + 1;
			for (int i = 0; i < n - 1; ++i)
				ae(i + 1, roads[i]), ae(roads[i], i + 1);
			for (int i = 0; i < n - 1; ++i)
				if (isImportant[i] == '1') 
					dem[i + 1] = ((initState[i] - '0') ^ 1);
			memset(f, 0x3f, sizeof(f));
			dfs(0);
			int ans = min(f[0][0], f[0][1]);
			return (ans + 1) / 2;
		}
};
