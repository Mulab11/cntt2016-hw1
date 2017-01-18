#line 2 "TheBrickTowerMediumDivOne.cpp"
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
//复杂度巨高巨麻烦的sb做法_(:з」∠)_
bool used[maxn]; // 标记第i个塔有没有被使用
int n, a[maxn], h[maxn], f[maxn][maxn][maxn][2][2]; // a从低到高放塔的编号，h放塔的高度，f[i][j][k][l][r], 表示，已经放了前i低的塔，现在有j块塔，它们有一侧可以继续放塔，有k块塔，它们的两侧都可以继续放塔，l是左端是否有塔，r是右端是否有塔……此时，已经放入的塔对总长度的最小贡献为f
bool cmp(const int &a, const int &b) { // 用于将塔的编号按高度排序
	return h[a] == h[b] ? a < b : h[a] < h[b];
}
int tmp[maxn], m; // m表示目前可用的塔的个数，tmp从小到大存它们的高度
void upd(int &a, int b) {
	if (b < a) a = b;
}
int calc(int left) {
	int det = left == 50 ? 50 : 0; // 特殊处理开始一个塔都没有的情况，此时，最左端塔和left(= 50)之间的距离为50，需要最后减去
	memset(f, 0x3f, sizeof(f));
	m = 0;
	for (int i = 1; i <= n; ++i)
		if (!used[a[i]]) tmp[++m] = h[a[i]]; // 把目前可用的塔高度放入tmp
	if (m == 0) return 0;
	if (m == 1) return max(left, tmp[1]) - det; // 若只有一个塔，距离就是它与left之间的距离
	f[0][0][0][0][0] = 0;
	for (int i = 1; i <= m; ++i) // 放第i低的塔
		for (int j = 0; j <= m; ++j) // 之前有j块塔，其一侧可以接着放塔
			for (int k = 0; k <= m; ++k) // 之前有k块塔，其两侧都可以接着放塔
				for (int l = 0; l <= 1; ++l) // l为1表示最左端已经放了塔
					for (int r = 0; r <= 1; ++r) // r为1表示最右端已经放了塔
						if (f[i - 1][j][k][l][r] != 0x3f3f3f3f) {
							int prev = f[i - 1][j][k][l][r];
							upd(f[i][j][k + 1][l][r], prev); // 新放入的塔比两边的塔都矮，k ++
							if (j + k >= 1) upd(f[i][j][k][l][r], prev + tmp[i]); // 新放入的塔比一边的矮，比一边的高，可能是在j中某块塔的一侧放下了i，也可能是在k中某块塔的一侧放下了i，j与k都不变
							if (j == 2 && i == m && k == 0 && l && r) upd(f[i][j - 2][k][l][r], prev + 2 * tmp[i]); // 新放入的塔比两边都高，且两边都是只有一侧可以放塔的类型，这种情况只会在最后一步发生
							if ((j >= 1 && k >= 1) || k >= 2) upd(f[i][j][k - 1][l][r], prev + 2 * tmp[i]); // 新放入的塔比两边高，且一边属于j/k，一边属于k，k --
							if (r == 0) {
								upd(f[i][j + 1][k][l][1], prev); // 放在最右侧，且左边的比它高
								if (j == 1 && i == m && k == 0 && l) upd(f[i][j - 1][k][l][1], prev + tmp[i]); // 放在最右侧，左边的比他低，且是j的类型，这种情况只能在最后一步发生
								if (k >= 1) upd(f[i][j + 1][k - 1][l][1], prev + tmp[i]); // 放在最右侧，左边的比他低，且属于k，它从两侧都能放的k变成了只有一侧能放的j
							}
							if (l == 0) { // 放在左端同理，区别在于还需要加上它与left之间的距离
								upd(f[i][j + 1][k][1][r], prev + max(left, tmp[i]));
								if (j == 1 && i == m && k == 0 && r) upd(f[i][j - 1][k][1][r], prev + max(left, tmp[i]) + tmp[i]);
								if (k >= 1) upd(f[i][j + 1][k - 1][1][r], prev + max(left, tmp[i]) + tmp[i]);
							}
						}
	return f[m][0][0][1][1] - det; 
}

class TheBrickTowerMediumDivOne {
	public:
		vector <int> find(vector <int> heights) {
			cl(used);
			n = heights.size();
			for (int i = 0; i < n; ++i) h[i + 1] = heights[i], a[i + 1] = i + 1;
			sort(a + 1, a + n + 1, cmp);
			int ans = calc(50), now = 0; vector <int> ret; // ans是最小距离，now存当前放了的i个塔之间的距离，ret存放答案
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) 
					if (!used[j]) { // 对每一位，都尝试放下字典序尽量小的塔
						used[j] = 1;
						int tmp = calc(h[j]);
						if (i >= 2) tmp += max(h[ret[i - 2] + 1], h[j]); // tmp为放下塔j后，所能达到的最小距离
						if (now + tmp == ans) { // 若所能达到的最小距离与答案相符，这一位就放塔j
							ret.pb(j - 1); 
							if (i >= 2) now += max(h[ret[i - 2] + 1], h[ret[i - 1] + 1]);
							break;
						}
						used[j] = 0;
					}
			}
			return ret;
		}
};

