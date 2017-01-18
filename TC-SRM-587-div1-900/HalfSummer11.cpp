#line 2 "ThreeColorability.cpp"
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
   可以发现方案不合法，仅当出现一个田字形，其中三条对角线方向相同，另一条对角线方向和它们不同。问题转化为，给出一个部分填好的01矩阵，要求把它填满，满足任意一个2*2的矩形内数字xor和为0，且字典序最小。
   假设枚举第一行中，相邻两个格子内数字是否相同，则对于接下来的每一行，相邻两个格子内数字的同异情况必须与第一行相同。反过来，只要保证每一行内相邻两个格子的同异情况都一样，矩阵就是合法的。
   给出的信息相当于规定了同一行内，列与列之间的相同/不同关系。用并查集维护。然后，再从第一个格子开始，先由已有的信息尽量填上格子，再贪心。
*/
int n, m, fa[maxn * 2], op[maxn * 2]; // n, m是矩阵的行数和列数，fa[]存并查集的根，op[]存相反的并查集。
int find(int x) { // 找到x所在并查集的根
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
bool merge(int x, int y) { // 合并x,y所在并查集。若x,y已经规定是不同的，返回0
	x = find(x); y = find(y);
	if (x == y) return 1;
	if (op[x] == y) return 0; // x, y不可以在一个并查集内
	fa[x] = y; fa[op[x]] = op[y];
	return 1;
}
class ThreeColorability {
	public:
		vector <string> lexSmallest(vector <string> G) {
			n = G.size(); m = G[0].size();
			for (int i = 1; i <= m; ++i) { // 对每一列i，建立i + m表示与它相反的并查集
				fa[i] = i; fa[i + m] = i + m;
				op[i] = i + m; op[i + m] = i;
			}
			vector <string> ans;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					for (int k = j + 1; k < m; ++k) { // 利用每行的已有信息增加限制
						if (G[i][j] == '?' || G[i][k] == '?') continue;
						if (G[i][j] == G[i][k] && !merge(j + 1, k + 1)) return ans; // 出现矛盾
						if (G[i][j] != G[i][k] && !merge(j + 1, k + m + 1)) return ans;
					}
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j)
					if (G[i][j] != '?') // 先根据已有信息推断剩下的格子
						for (int k = 0; k < m; ++k) {
							if (find(k + 1) == find(j + 1)) 
								G[i][k] = G[i][j];
							if (find(k + 1) == op[find(j + 1)])
								G[i][k] = 'N' + 'Z' - G[i][j];
						}
				for (int j = 0; j < m; ++j)
					if (G[i][j] == '?') {
						G[i][j] = 'N'; // 不受已有信息限制，贪心
						for (int k = 0; k < m; ++k) {
							if (find(k + 1) == find(j + 1))
								G[i][k] = G[i][j];
							if (find(k + 1) == op[find(j + 1)])
								G[i][k] = 'N' + 'Z' - G[i][j];
						}
					}
				for (int j = 0; j < m; ++j) // 这一行确定后，列和列之间的相同/不同关系也随之确定，加入相关的限制
					for (int k = j + 1; k < m; ++k) {
						if (G[i][j] != G[i][k]) merge(j + 1, k + m + 1);
						if (G[i][j] == G[i][k]) merge(j + 1, k + 1);
					}
			}
			return G;
		}
};
