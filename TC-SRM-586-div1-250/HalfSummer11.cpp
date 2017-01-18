#line 2 "PiecewiseLinearFunction.cpp"
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
#define maxn 110
typedef long long ll;
using namespace std;
class PiecewiseLinearFunction {
	public:
		int maximumSolutions(vector <int> Y) {
			int n = Y.size(), ans = 0; 
			for (int i = 0; i < n - 1; ++i)
				if (Y[i] == Y[i + 1]) return -1; // 此时答案为oo
			for (int vi = 0; vi < n; ++vi) {
				for (double k = -0.5; k <= 0.5; k += 0.5) { // 答案一定在拐点 / 拐点往上 / 下一点的地方取到
					double v = Y[vi] + k; int now = 0;
					for (int i = 0; i < n - 1; ++i)
						if ((Y[i] < v && v < Y[i + 1]) || (Y[i + 1] < v && v < Y[i])) ++now;
					for (int i = 0; i < n; ++i)
						if (Y[i] == v) ++now; // 计算解的个数
					ans = max(ans, now);
				}
			}
			return ans;
		}
};
