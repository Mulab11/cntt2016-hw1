#line 2 "ColorfulBuilding.cpp"
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
#define maxn 1310
#define mo 1000000009
typedef long long ll;
using namespace std;
int n, vt, col[maxn], val[maxn]; // n是建筑总数，col[]是建筑颜色，val[]和vt用于离散化颜色
int f[maxn][maxn], O, sum[maxn]; // f([i])[j][k]表示放完第i - n个建筑，目前已有j段颜色，最后一段的颜色为k，的方案数。sum([i])[j] = \sum_{k = 0}^{vt} f([i])[j][k]
/*
   从大到小安排建筑，这样，高度为i的建筑或者放到最前面，变成可见的，或者放到任意一个之前建筑的后面，变成不可见的，有转移：
   1) k = col[i] : 
      f[i][j][k] += f[i + 1][j][k] * (n - i + 1); // 随便放哪里
      f[i][j][k] += f[i + 1][j - 1][p]; // p != k, 第i个建筑物可见
   2) k != col[i] :
      f]i][j][k] += f[i + 1][j][k] * (n - i); // 第i个建筑不可见
   直接转移是O(n ^ 3)的，注意到每次对于k != col[i], 无论j的取值，f都在上一步的基础上乘上了同一个数(n - i).每次不直接执行(2)中的转移，而是对每种颜色k记录tmp[k] = k != col[i]阶段(n - i)的积，使得真f = 当前f * tmp。对于(1)中的转移，增加辅助数组sum[], 推一推转移的式子，就能实现O(n ^ 2)了。
*/
int tmp[maxn]; // 实际f[j][c] = 当前f[j][c] * tmp[c]
void add(int &a, int b) {
	a += b; a %= mo;
}
class ColorfulBuilding {
	public:
		int count(vector <string> color1, vector <string> color2, int L) {
			string col1 = "", col2 = "";
			for (int i = 0; i < color1.size(); ++i) col1 = col1 + color1[i];
			for (int i = 0; i < color2.size(); ++i) col2 = col2 + color2[i];
			n = col1.size();
			for (int i = 0; i < n; ++i) 
				val[i] = col[i + 1] = int(col1[i]) * 256 + int(col2[i]); // 将字符串映射到整数
			sort(val + 0, val + n);
			vt = unique(val + 0, val + n) - val;
			for (int i = 0; i < n; ++i) 
				col[i + 1] = lower_bound(val + 0, val + vt, col[i + 1]) - val; // 将颜色离散化
			col[0] = vt;
			cl(f); cl(sum);
			f[1][col[n]] = 1; sum[1] = 1; // 先放最高的建筑
			for (int i = 0; i <= vt; ++i) tmp[i] = 1;
			for (int i = n - 1; i >= 1; --i) {
				int c = col[i];
				for (int j = n; j >= 0; --j) 
					f[j][c] = 1ll * f[j][c] * tmp[c] % mo; // 得到f[i + 1][j][c]
				tmp[c] = 1; // f[][c]已经更新，tmp归1
				for (int j = n; j >= 0; --j) {
					sum[j] = 1ll * sum[j] * (n - i) % mo;
					add(sum[j], f[j][c]);
					if (j) add(sum[j], sum[j - 1]);
					if (j) add(sum[j], mo - f[j - 1][c]);
					f[j][c] = 1ll * f[j][c] * (n - i + 1) % mo;
					if (j) add(f[j][c], sum[j - 1]);
					if (j) add(f[j][c], mo - f[j - 1][c]);
				}
				for (int j = 0; j <= vt; ++j) // 对于j != col[i], 所有f在原来基础上乘上(n - i)
					if (j != c) tmp[j] = 1ll * tmp[j] * (n - i) % mo;
			}
			int ans = 0;
			for (int i = 0; i <= vt; ++i)
				add(ans, 1ll * f[L][i] * tmp[i] % mo);
			return ans;
		}
};
