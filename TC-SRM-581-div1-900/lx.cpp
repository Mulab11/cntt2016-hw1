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

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

template<typename T>
inline void read(T & x) {
	char c;
	while ((c = getchar()) < '0' || c > '9');
	for (x = c - '0'; (c = getchar()) >= '0' && c <= '9'; x = x * 10 + c - '0');
}

const int inf = 0x3f3f3f3f;
const int N = 14;

class YetAnotherBoardGame {
private :
	int bits[1 << 13 | 1];
	int w[N], n, m, tot;
	inline int f1(int x) {
		return (x ^ (x << 1) ^ (x >> 1)) & tot;
	}
	inline int f2(int x) {
		return ((x << 1) ^ (x >> 1)) & tot;
	}
	int Dfs(int step, int need, int now, int S1, int S2) {
		if (step == n) {
			return need ? inf : 0;
		}
		int x1 = need & S1, x2 = need & S2, res = need ^ x1 ^ x2;
		if (x1) {
			if (x2)  return inf;
			x1 |= res;
			return bits[x1] + Dfs(step + 1, now ^ f1(x1), w[step + 1] ^ x1, S1 | res, S2);
		} else if (x2) {
			x2 |= res;
			return bits[x2] + Dfs(step + 1, now ^ f2(x2), w[step + 1] ^ x2, S1, S2 | res);
		} else {
			return bits[res] + 
				min(Dfs(step + 1, now ^ f1(res), w[step + 1] ^ res, S1 | res, S2),
					Dfs(step + 1, now ^ f2(res), w[step + 1] ^ res, S1, S2 | res));
		}
	}
public :
	int minimumMoves(vector<string> board) {
		n = board.size(), m = board[0].size();
		tot = bin(m) - 1;
		rep (i, 0, n - 1) {
			rep (j, 0, m - 1) {
				if (board[i][j] == 'W')
					w[i] |= bin(j);
			}
		}
		int ans = inf;
		rep (i, 1, tot) {
			bits[i] = bits[i - (i & -i)] + 1;
		}
		rep (i, 0, tot) {
			upmin(ans, bits[i] + Dfs(1, w[0] ^ f1(i), w[1] ^ i, i, 0));
			upmin(ans, bits[i] + Dfs(1, w[0] ^ f2(i), w[1] ^ i, 0, i));
		}
		return ans < inf ? ans : -1;
	}
};
