#line 2 "Stamp.cpp"
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
int n, f[maxn][maxn]; // f[l][r]表示将[l,r]合法染色所需的最少次数
bool same[maxn][maxn]; // same[l][r]表示[l,r]能否被染成同一种颜色
class Stamp {
	public:
		int getMinimumCost(string goal, int S, int P) {
			n = goal.size();
			cl(same);
			for (int l = 1; l <= n; ++l)
				for (int r = l; r <= n; ++r) {
					char c = '*'; bool flag = 1; // 处理same
					for (int k = l - 1; k <= r - 1; ++k)
						if (goal[k] != '*' && goal[k] != c) {
							if (c == '*') c = goal[k]; else flag = 0;
						}
					if (flag) same[l][r] = 1;
				}
			int ans = oo;
			for (int L = 1; L <= n; ++L) { // 枚举印章的长度L
				memset(f, 0x3f, sizeof(f));
				for (int l = n; l >= 1; --l)
					for (int r = l; r <= n; ++r) {
						if (r - l + 1 < L) continue;
						if (same[l][r])
							f[l][r] = (r - l + 1 + L - 1) / L; // 若可以染成同一种颜色，染的最少次数是ceil(len / L)
						else {
							for (int mid = l + 1; mid <= r; ++mid) // 否则，枚举一个中间点，两边分别染色
								f[l][r] = min(f[l][r], f[l][mid - 1] + f[mid][r]);
						}
					}
				if (f[1][n] < oo)
					ans = min(ans, L * S + f[1][n] * P);
			}
			return ans;
		}
};
