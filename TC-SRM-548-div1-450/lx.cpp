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

class KingdomAndDice {
private :
	int num[52];
	bitset<2511> f[52];		//f[i][j] 表示用了 i 个 '0'，有 j 组 fir[x]>sec[y] 的 (x,y)
	int n, m;
public :
	//DP
	//压位，多重背包二进制分组
	//复杂度 O(n^4\log n / w)
	double newFairness(vector<int> fir, vector<int> sec, int X) {
		n = fir.size();
		sec.pb(X + 1);
		sort(sec.begin(), sec.end());
		int val = 0;
		rep (i, 0, n-1) {
			if (fir[i] == 0) {
				++m;
			} else {
				int v = lower_bound(sec.begin(), sec.end(), fir[i]) - sec.begin();
				val += v;
				num[v]++;
			}
		}
		f[0][val] = 1;
		rep (i, 1, sec.size()-1) {
			int cnt = sec[i] - sec[i - 1] - num[i] - 1;	
			// 在区间 (sec[i-1], sec[i]) 中还能填 cnt 个数
			// 其中每个数对答案贡献 i，多重背包问题转二进制分组
			for (int l = 1; l <= cnt; cnt -= l, l *= 2) {
				int v = i * l;
				down (s, m-l, 0)  f[s + l] |= f[s] << v;
			}
			if (cnt) {
				int v = i * cnt;
				down (s, m-cnt, 0)  f[s + cnt] |= f[s] << v;
			}
		}
		rep (i, 0, m-1)  f[m] |= f[i];
		int ans = -1;
		rep (i, 0, n*n) if (f[m][i]) {		// 统计最优答案
			if (ans == -1 || abs(2 * i - n * n) < abs(2 * ans - n * n)) {
				ans = i;
			}
		}
		return (double) ans / (n * n);
	}
};
