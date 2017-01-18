#line 2 "SpellCards.cpp"
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
int n, f[maxn][maxn], g[maxn][maxn][maxn]; // n是卡片的张数，卡片按照顺时针顺序排成一圈，f[i][j]表示把第i张牌到第j张牌（顺时针顺序）全部消掉，所能达到的最大伤害。g[i][j][rest]表示把从第i张牌到第j张牌（顺时针顺序）消到剩下rest张牌，所能达到的最大伤害。
class SpellCards {
	public:
		int maxDamage(vector <int> L, vector <int> D) {
			memset(f, -0x3f, sizeof(f));
			memset(g, -0x3f, sizeof(g));
			n = L.size();
			for (int i = 1; i <= n; ++i) { // 处理len = 1，单张牌的情况
				g[i][i][1] = 0; // 不消去
				if (L[i - 1] == 1) // 可以恰好只消去自己
					f[i][i] = g[i][i][0] = D[i - 1];
			}
			for (int len = 2; len <= n; ++len) { // 枚举区间长度len
				for (int l = 1; l <= n; ++l) { // 枚举开始点l
					int r = (l + len - 2) % n + 1; // 结束点r
					for (int mid = l; mid != r; mid = mid % n + 1) { // 若l和r不是被同时消去，枚举分界点mid
						f[l][r] = max(f[l][r], f[l][mid] + f[mid % n + 1][r]);
					}
					for (int rest = 1; rest <= len; ++rest) { // 处理g[l][r][rest]
						g[l][r][rest] = max(g[l][r][rest], g[l][(r == 1) ? n : r - 1][rest - 1]); // 不把r消去
						for (int lst = l % n + 1; ; lst = lst % n + 1) { // 把lst - r的部分消去
							g[l][r][rest] = max(g[l][r][rest], g[l][(lst == 1) ? n : lst - 1][rest] + f[lst][r]);
							if (lst == r) break;
						}
					}
					if (L[l - 1] <= len) // 若l和r是同时被消去
						f[l][r] = max(f[l][r], g[l % n + 1][r][L[l - 1] - 1] + D[l - 1]); // 注意，需要保证l还存在，所以用g[l % n + 1][r][]
					g[l][r][0] = f[l][r]; // 处理全部消去的情况
				}
			}
			int ans = 0;
			for (int l = 1; l <= n; ++l) // 把环从l处切开
				for (int rest = 0; rest <= n; ++rest)
					ans = max(ans, g[l % n + 1][l][rest]);
			return ans;
		}
};
