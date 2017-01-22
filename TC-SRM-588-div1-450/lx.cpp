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

const int M = bin(12);

class KeyDungeonDiv1 {
private :
	int cnt[M + 1];
	int f[M+1][121];
public :
	//状压DP
	//cnt[S] 表示集合 S 中所有门的钥匙总收益-钥匙总支出
	//f[S][i] 表示开过的门集合为 S，有红钥匙 i，最多可能有多少白钥匙
	//由 cnt[S]、i、f[S][i] 可以推算出绿钥匙的个数
	int maxKeys(vector<int> dR, vector<int> dG, vector<int> rR, vector<int> rG,
			vector<int> rW, vector<int> me) {
		int n = dR.size();
		memset(f, -1, sizeof(f));
		memset(cnt, -1, sizeof(cnt));
		int sr = me[0], tot = me[0] + me[1] + me[2];
		cnt[0] = 0;
		rep (i, 0, n-1) {
			cnt[bin(i)] = rR[i] + rG[i] + rW[i] - dR[i] - dG[i];
			sr += rR[i];
		}
		int ans = cnt[0];
		f[0][me[0]] = me[2];
		rep (i, 0, bin(n)-1) {
			if (cnt[i] == -1) {
				cnt[i] = cnt[i & -i] + cnt[i - (i & -i)];
			}
			rep (j, 0, sr) {
				if (f[i][j] >= 0) {
					int r = j, w = f[i][j], g = tot + cnt[i] - r - w;
					upmax(ans, cnt[i] + tot);
					rep (k, 0, n-1) {
						if (!(i & bin(k))) {
							int tr = max(r - dR[k], 0) + rR[k];
							int tw = w - max(dR[k] - r, 0) - max(dG[k] - g, 0);
							if (tw >= 0) {
								upmax(f[i | bin(k)][tr], tw + rW[k]);
							}
						}
					}
				}
			}
		}
		return ans;
	}
};
