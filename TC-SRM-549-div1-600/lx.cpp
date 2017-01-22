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

const int inf = 0x3f3f3f3f;
const int M = 1611111;

class MagicalHats {
private :
	vector<pii> hats;
	int nG, nR, nH;
	int cnth, cntc;
	int pow3[15];

	int get_d(int x, int k) {			//取出三进制下某一位
		return x / pow3[k] % 3;
	}
	int set_d(int x, int k, int v) {	//三进制下改变特定的某一位
		return (x / pow3[k+1]) * pow3[k+1] + v * pow3[k] + x % pow3[k];
	}

	bool vis[M];
	int dp[M];
	// 因为B可以给A面值尽可能小的硬币，所以答案只与最多能拿到多少硬币有关
	// dp[S] 表示帽子猜测状态为 S 的时候，A 最多能拿到多少硬币 
	// S 可以压成3进制数，每一位为0,1,2分别表示还没有猜这个帽子、猜了并且有硬币、猜了但是没有得到硬币
	int Rcnt[15], Ccnt[15];

	int rec(int state, int nh, int nc) {
		if (nh == cnth) {			//检查状态合法性
			if (nc != cntc)  return -inf;
			rep (i, 0, nR-1) if (Rcnt[i] & 1)  return -inf;
			rep (i, 0, nH-1) if (Ccnt[i] & 1)  return -inf;
			return 0;
		}
		if (vis[state]) return dp[state];
		vis[state] = 1;
		int ans = -inf;
		rep (i, 0, cnth-1) {		//转移的时候先枚举猜某个还没有猜的位置，再枚举这个位置放不放硬币
			int r = hats[i].x, c = hats[i].y;
			int v = get_d(state, i);
			if (v == 0) {
				int res1 = -inf, to;
				if (nc < cntc) {
					int now = (nh < nG);
					to = set_d(state, i, 2);
					res1 = now + rec(to, nh+1, nc+1);
				}
				to = set_d(state, i, 1);
				Rcnt[r] ^= 1;
				Ccnt[c] ^= 1;
				int res2 = rec(to, nh+1, nc);
				Rcnt[r] ^= 1;
				Ccnt[c] ^= 1;
				if (res1 < 0)
					upmax(ans, res2);
				else if (res2 < 0)
					upmax(ans, res1);
				else 
					upmax(ans, min(res1, res2));
			}
		}
		return dp[state] = ans;
	}
public :
	//考虑状态压缩的动态规划
	int findMaximumReward(vector<string> board, vector<int> val, int nG) {
		this->nG = nG;
		sort(val.begin(), val.end());
		nR = board.size();
		nH = board[0].size();
		rep (i, 0, nR-1) {
			rep (j, 0, nH-1) {
				if (board[i][j] == 'H') {
					hats.pb(mp(i, j));
				}
			}
		}
		cnth = hats.size();
		cntc = val.size();
		pow3[0] = 1;
		rep (i, 1, cnth)  pow3[i] = pow3[i - 1] * 3;
		int cnt = rec(0, 0, 0);
		if (cnt < 0)  return -1;
		int ans = 0;
		rep (i, 0, cnt-1) ans += val[i];
		return ans;
	}
};
