#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class GUMIAndSongsDiv1 {
private :
	int f[52][52], n;
	// f[i][j] 表示已经唱了 j 首，最后一首是 i 的最小时间
public :
	//贪心思想，DP
	//决定要唱哪些歌之后，升序/降序唱不会让时间消耗更多
	//将所有歌按声调排序，DP即可
	int maxSongs(vector<int> du, vector<int> tone, int T) {
		n = tone.size();
		down (i, n-1, 0) {
			rep (j, 0, i-1) {
				if (tone[j] > tone[j + 1]) {
					swap(tone[j], tone[j + 1]);
					swap(du[j], du[j + 1]);
				}
			}
		}
		int ans = 0;
		memset(f, 0x3f, sizeof(f));
		rep (i, 0, n-1) f[i][1] = du[i];			//初始状态：第一首歌
		rep (i, 0, n-1) rep (j, 1, i+1) {
			if (f[i][j] <= T) {
				upmax(ans, j);				//更新答案
				rep (k, i+1, n-1) {			//枚举唱的下一首歌
					upmin(f[k][j + 1], f[i][j] + tone[k] - tone[i] + du[k]);
				}
			}
		}
		return ans;
	}
};
