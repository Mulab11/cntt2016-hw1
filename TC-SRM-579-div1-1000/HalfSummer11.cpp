#line 2 "RockPaperScissors.cpp"
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
#define clear(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define son e[i].t
#define oo 0x3f3f3f3f
#define maxn 51
typedef long long ll;
using namespace std;
double f[maxn][maxn][maxn][maxn]; // f[i][r][p][s]表示，目前已经投出石头布剪刀各r/p/s个，第i个骰子还没有投出去，的概率
double pr[maxn], pp[maxn], ps[maxn]; // pr[i], pp[i], ps[i]分别表示第i个骰子投出r/p/s的概率
int n; // 骰子个数
class RockPaperScissors {
	public:
		double bestScore(vector <int> Pr, vector <int> Pp, vector <int> Ps) {
			n = Pr.size(); double res = 0;
			for (int i = 1; i <= n; ++i) {
				pr[i] = Pr[i - 1] / 300.0;
				pp[i] = Pp[i - 1] / 300.0;
				ps[i] = Ps[i - 1] / 300.0;
			}
			for (int i = 1; i <= n; ++i) f[i][0][0][0] = 1; // 初始化
			for (int t = 1; t <= n; ++t) { // 以下的dp省略了一维t，实际上应该是f[t][i][r][p][s], 它表示，在 投出去的骰子编号均在[1, t]中 这个前提下，投出了r/p/s个rock/paper/scissors, 第i个骰子还未投出的概率。
				for (int m = t; m >= 0; --m) // 已经投出的骰子总数
					for (int r = 0; r <= m; ++r)
						for (int p = 0; r + p <= m; ++p) {
							int s = m - r - p;
							double q = 1.0 * m / t; // 由于有投出的骰子均是[1, t]中的这个前提，所以，第t个骰子已经被投出的概率是m / t
							for (int i = 1; i <= n; ++i) {
								f[i][r][p][s] = f[i][r][p][s] * (1.0 - q); // 第t个骰子没有被投出，此时，满足前一个阶段前提的f依然满足当前阶段的前提（r/p/s中依然只有[1, t]的骰子），直接转移
								if (i == t) continue; // 否则，第t个骰子在r/p/s中，如果i = t，自然这种情况的贡献是0
								if (r > 0) f[i][r][p][s] += f[i][r - 1][p][s] * pr[t] * q; // 考虑第t个骰子投出的是什么，乘上相应概率转移
								if (p > 0) f[i][r][p][s] += f[i][r][p - 1][s] * pp[t] * q;
								if (s > 0) f[i][r][p][s] += f[i][r][p][s - 1] * ps[t] * q;
							}
						}
			}
			for (int r = 0; r < n; ++r)
				for (int p = 0; r + p < n; ++p)
					for (int s = 0; r + p + s < n; ++s) { // 枚举每一种可能的状态
						double q = 1.0 / (n - r - p - s), sr = 0, sp = 0, ss = 0; // sr/sp/ss分别是此时抽取一个骰子，投出r/p/s的概率 
						for (int i = 1; i <= n; ++i) {
							sr += f[i][r][p][s] * pr[i]; // 当前骰子存在且投出了rock。其实这里应该再除以P[r][p][s]，表示在这一前提下第i个骰子未投出的概率。但是之后累计入答案时，还要再乘上P[r][p][s],两两抵消了
							sp += f[i][r][p][s] * pp[i];
							ss += f[i][r][p][s] * ps[i];
						}
						sr *= q; sp *= q; ss *= q; // 由于抽到每个骰子的概率是均等的，再除以q
						res += max(max(sr + 3.0 * ss, sp + 3.0 * sr), ss + 3.0 * sp); // 选择最优的策略
					}
			return res;
		}
};
