#line 2 "GUMIAndSongsDiv1.cpp"
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
   最优的方案里，歌的tune[]一定是单不增/单不降的。把歌按照tune[]排序dp即可。
*/
int n, h[maxn], tmp[maxn], a[maxn], b[maxn]; // n是歌的支数，h[], tmp[]用于将歌按照tune排序，a[], b[]存放排序后歌的长度/tune
int f[maxn][maxn]; // f[i][j]表示上一支歌是i，已经唱了j首，需要的最短时间
bool cmp(const int &a, const int &b) {
	return h[a] < h[b];
}
void gmin(int &a, int b) {
	if (b < a) a = b;
}
class GUMIAndSongsDiv1 {
	public:
		int maxSongs(vector <int> dur, vector <int> tone, int T) {
			n = tone.size();
			for (int i = 0; i < n; ++i) {
				tmp[i] = i; h[i] = tone[i];
			}
			sort(tmp + 0, tmp + n, cmp); // 按tune排序
			for (int i = 0; i < n; ++i)
				a[i + 1] = dur[tmp[i]], b[i + 1] = h[tmp[i]];
			memset(f, 0x3f, sizeof(f));
			f[0][0] = 0;
			for (int i = 0; i <= n; ++i)
				for (int j = 0; j <= n; ++j) 
					if (f[i][j] < oo) {
						for (int k = i + 1; k <= n; ++k) {  // 枚举下一首歌
							int cost = (i == 0) ? 0 : b[k] - b[i];
							gmin(f[k][j + 1], f[i][j] + cost + a[k]);
						}
					}
			for (int i = n; i >= 0; --i)
				for (int j = 0; j <= n; ++j)
					if (f[j][i] <= T) return i;
		}
};
