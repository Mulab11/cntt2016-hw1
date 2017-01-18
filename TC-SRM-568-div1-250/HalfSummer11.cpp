#line 2 "BallsSeparating.cpp"
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
int n, f[maxn][2][2][2]; // f[i][j][k][p]表示考虑前i个盒子，是否有R/G/B盒子的情况为j/k/p,此时前i个盒子里拿出来的球数的最小值
bool R, G, B;
void upd(int &a, int b) {
	if (b < a) a = b;
}
class BallsSeparating {
	public:
		int minOperations(vector <int> r, vector <int> g, vector <int> b) {
			R = G = B = 0; // R,G,B表示颜色为r/g/b的球是否存在（这里好像是多余的……题目保证都存在
			n = r.size();
			for (int i = 0; i < n; ++i) {
				R |= r[i]; G |= g[i]; B |= b[i];
			}
			memset(f, 0x3f, sizeof(f));
			f[0][0][0][0] = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < 2; ++j)
					for (int k = 0; k < 2; ++k)
						for (int p = 0; p < 2; ++p) {
							upd(f[i + 1][j | 1][k][p], f[i][j][k][p] + g[i] + b[i]); // 枚举第i个盒子中留下哪种颜色的球，进行转移
							upd(f[i + 1][j][k | 1][p], f[i][j][k][p] + r[i] + b[i]);
							upd(f[i + 1][j][k][p | 1], f[i][j][k][p] + r[i] + g[i]);
						}
			return (f[n][R][G][B] == oo) ? -1 : f[n][R][G][B];
		}
};
