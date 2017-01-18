#line 2 "RotatingBot.cpp"
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
#define maxn 510
typedef long long ll;
using namespace std;
bool V[maxn * 2][maxn * 2], *V1[maxn * 2], **vis; // vis[i][j]记录坐标(i,j)是否被访问过
int tot;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
class RotatingBot {
	public:
		int minArea(vector <int> a) {
			for (int i = 0; i < 2 * maxn; ++i) V1[i] = V[i] + maxn;
			vis = V1 + maxn;
			tot = a.size();
			cl(V);
			vis[0][0] = 1; int x = 0, y = 0;
			for (int i = 0; i < tot; ++i) {
				for (int j = 1; j <= a[i]; ++j) {
					x += dx[i % 4]; y += dy[i % 4];
					if (vis[x][y]) return -1; // 首先轨迹不可以重叠
					vis[x][y] = 1;
				}
			}
			if (tot > 3 && a[2] < a[0]) return -1; // 没有撞墙就停了
			if (tot > 4 && ((a[3] < a[1] - 1) || (a[3] == a[1] - 1 && a[2] > a[0]))) return -1; // 没有撞墙/撞起点就停了
			if (tot == 1) return a[0] + 1;
			if (tot == 2) return (a[0] + 1) * (a[1] + 1);
			if (tot == 3) return (a[1] + 1) * max(a[0] + 1, a[2] + 1);
			if (tot == 4) return max(a[1] + 1, a[3] + 1) * max(a[0] + 1, a[2] + 1); // 特判走了1~4步的情况
			x = 0; y = 0; cl(V); vis[0][0] = 1;
			int mxx = 0, mix = 0, mxy = 0, miy = 0;
			for (int i = 0; i < tot; ++i) {
				for (int j = 1; j <= a[i]; ++j) {
					x += dx[i % 4]; y += dy[i % 4];
					if (i < 4) {
						mxx = max(mxx, x); mix = min(mix, x);
						mxy = max(mxy, y); miy = min(miy, y); // 当步数多于4时，前4步就确定了边框（即使不是真 矩阵边框，也是机器人的最大活动范围了
					} else {
						if (x > mxx || x < mix || y > mxy || y < miy) return -1; // 走出了范围
					}
					vis[x][y] = 1;
				}
				int nx = x + dx[i % 4], ny = y + dy[i % 4];
				if (i >= 4 && i != tot - 1 && !(vis[nx][ny] || nx > mxx || nx < mix || ny > mxy || ny < miy)) return -1; // 没有撞墙/即将重叠就停了
			}
			return (mxx - mix + 1) * (mxy - miy + 1);
		}
};


