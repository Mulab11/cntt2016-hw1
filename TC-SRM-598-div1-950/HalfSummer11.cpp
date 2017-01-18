#line 2 "TPS.cpp"
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
int n, g[maxn], ei; // n是点数，g[], ei是边表
struct edge {
	int t, nxt;
}e[maxn * 2]; 
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
/*
   枚举一个选中的点，将它作为树根。接下来只需要区分相同深度的点。
   从深度为1的点开始，假设根有cnt个儿子，一对儿子相互区分，需要在至少其中一个的子树里选中了一个点。cnt个儿子相互区分，至少有cnt - 1个儿子内部需要选中点。
   考虑深度为2的点，两个父亲不同的点已经可以被区分开，只需要区分父亲相同的点，于是就可以变成一个子问题。
   递归解决，先区分每个儿子为根的子树内部的情况，再把内部选中了点的儿子个数补到cnt - 1
*/
int dfs(int x, int fa) { // 计算将以x为根的子树中的深度相同的点区分出来，需要选多少个点
	int ret = 0, zero = 0;
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != fa) {
			int tmp = dfs(e[i].t, x);
			ret += tmp; // 每个儿子子树内相互区分，所需要选的点数
			zero += (tmp == 0); // 记录子树里什么都没选的儿子个数
		}
	if (zero > 1) ret += zero - 1; // 为了区分这些儿子，最多只能有一个儿子的子树里没有选点，补上剩下zero - 1个儿子里的点
	return ret;
}
class TPS {
	public:
		int minimalBeacons(vector <string> linked) {
			n = linked.size();
			if (n == 1) return 0;
			cl(g); ei = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (linked[i][j] == 'Y') ae(i, j);
			int ans = n;
			for (int i = 0; i < n; ++i) 
				ans = min(ans, dfs(i, -1) + 1); // 考虑选中i为树根的情况
			return ans;
		}
};
