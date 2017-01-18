#line 2 "RandomPaintingOnABoard.cpp"
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
#define maxn 30
#define maxv 1400
/*
   令P(t)表示t时刻后满足条件的概率，期望时间 = \sum_{t = 1}^{oo} (P(t) - P(t - 1)) * t = \sum_{t = 0}^{oo} (1 - P(t)). 只需要计算每个时刻后未满足条件的概率。
   未满足条件，则至少有一行 / 一列没有格子被涂黑。考虑容斥，枚举一定没有被涂黑的行和列，可以算出t时刻后这些行/列未被涂黑的概率 = (sum(不在选中的行列中格子的Prob之和) / Prob总和) ^ t, t = 0 ~ oo, 前面式子的和 = 1 / (1 - (sum(不在选中的行列中格子的Prob之和) / Prob总和))
   直接枚举行列会超时，考虑枚举较小的一维（不会超过12），对于剩下的一维，以Prob之和（不超过150*9)为状态进行dp.
*/
int n, m, sum, a[maxn][maxn], b[maxn]; // n, m是棋盘的尺寸，sum = 所有的Prob之和，a[][]记录Prob，b[]用于记录保留一部分行的情况下，每列Prob的和
int f[maxn][maxv][2]; // f[i][s][j]表示考虑前i列，目前选择的列中Prob之和为s，且未选择的列奇偶性为j，的方案数
typedef long long ll;
using namespace std;
class RandomPaintingOnABoard {
	public:
		double expectedSteps(vector <string> prob) {
			n = prob.size(); m = prob[0].size();
			sum = 0;
			double ans = 0;
			if (m < n) { 
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < m; ++j)
						a[j + 1][i + 1] = prob[i][j] - '0', sum += prob[i][j] - '0';
				swap(n, m); // 令行数 < 列数，保证枚举行的选取情况时的复杂度
			} else {
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < m; ++j)
						a[i + 1][j + 1] = prob[i][j] - '0', sum += prob[i][j] - '0';
			}
			for (int sta = 0; sta < (1 << n); ++sta) { // 枚举可能变黑的行
				cl(b); int t = (n % 2);
				for (int j = 0; j < n; ++j)
					if (sta & (1 << j)) {
						t ^= 1; 
						for (int i = 1; i <= m; ++i)
							b[i] += a[j + 1][i]; // 计算留下sta中行时，每列的Prob之和
					}
				cl(f);
				f[0][0][0] = 1;
				for (int i = 1; i <= m; ++i)
					for (int j = 0; j <= (i - 1) * 9 * n; ++j)
						for (int k = 0; k <= 1; ++k) {
							f[i][j][k ^ 1] += f[i - 1][j][k]; // 不选择这一列
							f[i][j + b[i]][k] += f[i - 1][j][k]; // 选择这一列
						}
				for (int j = 0; j < sum; ++j)
					for (int k = 0; k <= 1; ++k)
						if (k ^ t)
							ans += 1.0 / (1.0 - 1.0 * j / sum) * f[m][j][k]; // sta以外的行、选中列以外的列,在一次选择中全都未被选中的概率是j / sum，期望被选中的时间为1 / (1 - j / sum)
						else
							ans -= 1.0 / (1.0 - 1.0 * j / sum) * f[m][j][k];
			}
			return ans;
		}
};
