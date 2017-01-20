#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 55;

int n;
pair<int, int> D[maxn];
int f[maxn][maxn];

class GUMIAndSongsDiv1 {
    public:
    int maxSongs(vector<int> duration, vector<int> tone, int T) {
		int Ans = 0;
		n = duration.size();
		for (int i = 1; i <= n; ++i) {
			D[i] = make_pair(tone[i - 1], duration[i - 1]);
		}
		sort(D + 1, D + 1 + n);//将所有的歌按照tone值排序
		memset(f, 0x3f, sizeof(f));
		for (int i = 1; i <= n; ++i) {//Dp：f[i][j]表示前i首歌选了j首的最短时间
			f[i][1] = D[i].second;//初始化时第一首歌不需要tone的转化时间
		}
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j <= i; ++j) {
				if (f[i][j] < 1e9) {
					Ckmin(f[i + 1][j], f[i][j] + D[i + 1].first - D[i].first);
					Ckmin(f[i + 1][j + 1], f[i][j] + D[i + 1].first - D[i].first + D[i + 1].second);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) {
				if (f[i][j] <= T) {
					Ckmax(Ans, j);//更新答案
				}
			}
		}
        return Ans;
    }
};
