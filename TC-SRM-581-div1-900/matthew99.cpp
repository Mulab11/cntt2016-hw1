#line 5 "YetAnotherBoardGame.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 13;

int n, m;
int a[maxn + 5], b[maxn + 5];

int ans;

int S;

inline void flip(int x, int y, int ty)
{
	b[x] ^= y << 1;
	b[x] ^= y >> 1;
	if (ty) b[x] ^= y;
	if (x + 1 < n) b[x + 1] ^= y;
	b[x] &= S, b[x + 1] &= S;
}

void dfs(int x, int ty0, int ty1, int step = 0)
{
	if (x == n - 1)
	{
		if (!b[x]) chkmin(ans, step);
		return;
	}
	int tmp0 = b[x + 1], tmp1 = b[x + 2], cnt = __builtin_popcount(b[x]);
	if (!(b[x] & ty1)) flip(x + 1, b[x], 0), dfs(x + 1, ty0 | b[x], ty1, step + cnt), b[x + 1] = tmp0, b[x + 2] = tmp1;
	if (!(b[x] & ty0)) flip(x + 1, b[x], 1), dfs(x + 1, ty0, ty1 | b[x], step + cnt), b[x + 1] = tmp0, b[x + 2] = tmp1;
}

class YetAnotherBoardGame
{
	public:
		int minimumMoves(vector <string> board)
		{
			n = SZ(board), m = SZ(board[0]);
			S = (1 << m) - 1;
			REP(i, 0, n)
			{
				a[i] = 0;
				REP(j, 0, m) if (board[i][j] == 'W') a[i] |= 1 << j;
			}
			ans = oo;
			REP(ty, 0, 2)
			{
				REP(i, 0, 1 << m)
				{
					if (ty && !i) continue;
					memcpy(b, a, sizeof b);
					flip(0, i, ty);
					int cnt = __builtin_popcount(i);
					if (ty) dfs(0, 0, i, cnt);
					else dfs(0, i, 0, cnt);
				}
			}
			return ans < oo ? ans : -1;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
