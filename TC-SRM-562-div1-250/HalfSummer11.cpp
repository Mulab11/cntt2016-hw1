#line 2 "PastingPaintingDivOne.cpp"
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
#define maxn 120
#define sz 110
typedef long long ll;
using namespace std;
char board[maxn][maxn]; // 画布
int r, c, cnt[3][maxn]; // r/c是clipboard的尺寸，cnt[i][j]表示一次粘贴得到的内容，在又覆盖了j次后，剩下的第i种颜色的个数
class PastingPaintingDivOne {
	public:
		vector<long long> countColors(vector <string> clip, int T) {
			for (int i = 0; i <= sz; ++i)
				for (int j = 0; j <= sz; ++j)
					board[i][j] = '.'; // 初始是透明的
			r = clip.size(); c = clip[0].size();
			cl(cnt);
			for (int i = 0; i < r; ++i)
				for (int j = 0; j < c; ++j) {
					board[i][j] = clip[i][j]; // 第一次粘贴，直接改变了画布上的颜色
					if (board[i][j] == 'R') ++cnt[0][0]; // 在没有进行第二次粘贴时，R/G/B的个数就是clipboard上R/G/B的个数
					if (board[i][j] == 'G') ++cnt[1][0];
					if (board[i][j] == 'B') ++cnt[2][0];
				}
			for (int step = 1; step <= 50; ++step) { // 由于clipboard的尺寸有限，第50+次覆盖时，覆盖的范围已经不会与开始的图案重合，因此只需要考虑被覆盖1-50次的情况
				for (int i = 0; i < 3; ++i) cnt[i][step] = cnt[i][step - 1];
				for (int i = 0; i < r; ++i)
					for (int j = 0; j < c; ++j)
						if (clip[i][j] != '.') {
							if (board[step + i][step + j] == 'R') --cnt[0][step]; // 若在这一次被覆盖了，这种颜色个数--
							if (board[step + i][step + j] == 'G') --cnt[1][step];
							if (board[step + i][step + j] == 'B') --cnt[2][step];
							board[step + i][step + j] = '.'; // 已经被覆盖，不能在之后的step中被计算
						}
			}
			vector <ll> ret;
			for (int i = 0; i <= 2; ++i) ret.pb(0ll);
			if (T - 1 <= 50ll) {
				for (ll i = 0; i < T; ++i) // 从右下角往上，依次是被覆盖了0,1, .. T - 1次的图案
					for (int j = 0; j <= 2; ++j)
						ret[j] += cnt[j][i]; 
			} else {
				for (ll i = 0; i <= 50ll; ++i)
					for (int j = 0; j <= 2; ++j)
						ret[j] += cnt[j][i];
				for (int j = 0; j <= 2; ++j)
					ret[j] += 1ll * (T - 51ll) * cnt[j][50]; // 被覆盖超过50次的(T - 51)个图案，cnt与被覆盖50次的一样
			}
			return ret;
		}
};
