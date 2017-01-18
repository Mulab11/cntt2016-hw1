#line 2 "BoundedOptimization.cpp"
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
#define maxn 20
typedef long long ll;
using namespace std;
int n, a[maxn][maxn]; // a[i][j] = 1表示expr中存在x_i * x_j
double x[maxn], c[maxn]; // x存放变量的值，c存放求偏导时的一些量……
double mx;
class BoundedOptimization {
	public:
		double maxValue(vector <string> expr, vector <int> L, vector <int> R, int maxSum) {
			n = L.size(); cl(a); mx = 0;
			string tmp = ""; // 以下，把expr中的信息读入
			for (int i = 0; i < expr.size(); ++i) tmp = tmp + expr[i];
			int pos = 0;
			while (pos < tmp.size()) {
				if (tmp[pos] == '+') {
					++pos; 
				} else {
					int t1 = tmp[pos] - 'a', t2 = tmp[++pos] - 'a';
					a[t1][t2] = a[t2][t1] = 1;
					++ pos; 
				}
			}
			int sum = 0;
			for (int i = 0; i < n; ++i) sum += R[i];
			if (sum <= maxSum) { // 此时，所有变量可以直接取到上界
				double ans = 0;
				for (int i = 0; i < n; ++i)
					for (int j = i + 1; j < n; ++j)
						if (a[i][j])
							ans += R[i] * R[j];
				return ans;
			}
			for (int s = 0; s < (1 << n); ++s) // 枚举被确定为上界/下界的变量的集合
				for (int t = s; ; t = (t - 1) & s) { // 枚举被确定为下界的变量的集合
					for (int i = 0; i < n; ++i)
						if (s & (1 << i)) {
							if (t & (1 << i)) {
								x[i] = L[i];
							} else {
								x[i] = R[i];
							}
						}
					bool flag = 1;
					for (int i = 0; i < n; ++i)
						for (int j = i + 1; j < n; ++j)
							if (!(s & (1 << i)) && !(s & (1 << j)) && !a[i][j]) flag = 0; // 若枚举到的，不在边界上的两个变量i,j,x_i * x_j 没有出现在expr中，说明不是以下算法可以奏效的情况
					if (!flag) {
						if (!t) break; else continue;
					}
					double sum = maxSum; // sum存不在边界上的变量的和。 这些变量两两组合都出现在了expr里，使用拉格朗日乘数法，对每个变量求偏导，形式是0 = sum / 2 + 已经确定下来且a_{i, j} = 1的x_j的和 + lambda - x_i
					for (int i = 0; i < n; ++i)
						if (!(s & (1 << i))) {
							c[i] = 0;
							for (int j = 0; j < n; ++j)
								if ((s & (1 << j)) && a[i][j])
									c[i] += x[j]; // c[i] 等于已经确定下来且a_{i, j} = 1的x_j的和
						} else {
							sum -= x[i];
						}
					if (sum < 0) {
						if (!t) break; else continue;
					}
					double delta = sum; int cnt = 0;
					for (int i = 0; i < n; ++i)
						if (!(s & (1 << i))) {
							c[i] += sum * 0.5; // 再加上 sum / 2
							delta -= c[i]; // 由于x_i之和为sum,cnt * lambda = sum - \sum c[i]
							++cnt;
						}
					delta /= cnt; // 解出lambda
					for (int i = 0; i < n; ++i)
						if (!(s & (1 << i)))
							x[i] = c[i] + delta; 
					for (int i = 0; i < n; ++i)
						if (x[i] < L[i] - 1e-12 || x[i] > R[i] + 1e-12) flag = 0; // 需要在范围内
					if (!flag) {
						if (!t) break; else continue;
					}
					double ans = 0;
					for (int i = 0; i < n; ++i)
						for (int j = i + 1; j < n; ++j)
							if (a[i][j]) ans += x[i] * x[j];
					mx = max(ans, mx);
					if (!t) break;
				}
			return mx;
		}
};
