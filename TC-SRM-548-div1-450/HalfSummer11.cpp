#line 2 "KingdomAndDice.cpp"
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
/* 获胜概率 = n * n种可能出现的情况中，获胜的情况数 / (n * n)
   用bool背包来做。可以选择的点数相当于是物品。
*/
int n, m, sum, b[maxn]; // b存第二个骰子上的点数，sum存第一个骰子上已有的点数和第二个骰子上的点数相较，已经能赢得的场数
int cnt[maxn]; // cnt[i]表示恰好比i个第二个骰子上的点数大的、可供选择的点数个数
bool F[2][maxn][maxn * maxn]; // now[i][j] 表示选择i个点数填入第一个骰子，这些点数与第二个骰子上的点数相较，是否可能恰好赢j场
int O;
#define now F[O]
#define last F[O ^ 1]
#define eps 1e-9
int dcmp(double x) {
	return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;
}
class KingdomAndDice { 
	public:
		double newFairness(vector <int> fD, vector <int> sD, int X) {
			cl(F); cl(cnt); 
			m = n = fD.size(); sum = 0;
			for (int i = 0; i < n; ++i) b[i + 1] = sD[i];
			sort(b + 1, b + n + 1);
			for (int i = 1; i <= n; ++i) 
				cnt[i] = (i == n) ? X - b[i] : b[i + 1] - b[i] - 1;
			for (int i = 0; i < n; ++ i)
				if (fD[i] != 0) {
					int pos = lower_bound(b + 1, b + n + 1, fD[i]) - b - 1;
					--cnt[pos];
					sum += pos;
					--m;
				}
			now[0][0] = 1;
			for (int i = 1; i <= n; ++i) {
				int tot;
				for (int j = 0; ; ++j) {
					if (! cnt[i]) break;
					if (cnt[i] < (1 << j)) tot = cnt[i]; else tot = (1 << j); // 多重背包，二进制分组
					O ^= 1; memcpy(now, last, sizeof(now)); cnt[i] -= tot; 
					for (int k = 0; k + tot <= m; ++k)
						for (int p = 0; p + tot * i <= n * n; ++p)
							now[k + tot][p + tot * i] |= last[k][p];
				}
			}
			double min = 1000, ans;
			for (int i = 0; i <= n * n; ++i) {
				bool flag = 0;
				for (int j = 0; j <= m; ++j) flag |= now[j][i];
				if (flag) {
					double tmp = (i + sum) / 1.0 / (n * n);
					int res = dcmp(fabs(tmp - 0.5) - min);
					if (res < 0 || (res == 0 && tmp < ans)) { // “当差的绝对值相同时，输出概率较小的一个”
						ans = tmp;
						min = fabs(ans - 0.5);
					}
				}
			}
			return ans;
		}
		

};


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
