#line 2 "WallGameDiv1.cpp"
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
   对于Eel来说，每次或者放块挡板不让Rabbit往下走，或者把别的位置放满强行让它往下走，对于后面的情况，直接转移到下一行，对于前面的情况，仅当Rabbit走进一个格子，Eel才会在这里放挡板。
   于是，每行里放挡板的位置是连续的一段，并且Rabbit当前走到的格子位于这一段的某一端，没有放挡板。
   用f[i][l][r][0]表示Rabbit在第i行的第r个位置，且[l, r - 1]都放了挡板，此时走到终点的最小代价。枚举Eel是否放挡板，若放挡板，枚举Rabbit往哪边走更优。
*/
int n, m, f[maxn][maxn][maxn][2], w[maxn][maxn], sum[maxn][maxn]; // n, m是board的尺寸。f[i][l][r][0/1]的含义见上。w[i][j]是位置(i, j)的代价，sum是w的前缀和
void gmin(int &a, int b) {
	if (b < a) a = b;
}
class WallGameDiv1 {
	public:
		int play(vector <string> costs) {
			n = costs.size(); m = costs[0].size();
			cl(w); cl(sum);
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					w[i + 1][j + 1] = costs[i][j] - '0';
					sum[i + 1][j + 1] = sum[i + 1][j] + w[i + 1][j + 1];
				}
			}
			memset(f, 0x3f, sizeof(f));
			for (int i = 1; i <= m; ++i)
				f[n][i][i][0] = f[n][i][i][1] = 0; // 对于最后一行，代价是0
			for (int i = n - 1; i >= 1; --i) 
				for (int len = m - 1; len >= 0; --len)
					for (int l = 1; l + len <= m; ++l) {
						int r = l + len;
						int down = w[i + 1][r] + f[i + 1][r][r][0]; // 强行让它往下走的代价
						if (r == m && l == 1) // 此时只能往下走
							gmin(f[i][l][r][0], down);
						else {
							int stay = oo;
							if (r < m) // 向右走
								gmin(stay, w[i][r + 1] + f[i][l][r + 1][0]);
							if (l > 1) // 向左走
								gmin(stay, sum[i][r - 1] - sum[i][l - 2] + f[i][l - 1][r][1]);
							gmin(f[i][l][r][0], max(down, stay));
						}
						down = w[i + 1][l] + f[i + 1][l][l][0];
						if (l == 1 && r == m) 
							gmin(f[i][l][r][1], down);
						else {
							int stay = oo;
							if (l > 1)
								gmin(stay, w[i][l - 1] + f[i][l - 1][r][1]);
							if (r < m)
								gmin(stay, sum[i][r + 1] - sum[i][l] + f[i][l][r + 1][0]);
							gmin(f[i][l][r][1], max(down, stay));
						}
					}
			int ans = oo;
			for (int j = 1; j <= m; ++j)
				gmin(ans, w[1][j] + f[1][j][j][0]);
			return ans;
		}
};
