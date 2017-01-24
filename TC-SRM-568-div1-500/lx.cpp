#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 7;
const int N = 105;

class EqualSums
{
public:
	vector<string> G;

	bool vis[N];
	int num[N], n;

	bool dfs(int x)
	{
		vis[x] = 1;
		rep (i, 0, n - 1) 
		{
			char c = x < n ? G[x][i] : G[i][x - n];
			int to = x < n ? i + n : i;
			if (c != '-')
			{
				int v = c - '0' - num[x];
				if (v < 0 || (num[to] != -1 && num[to] != v))
					return 0;
				if (num[to] == -1)
				{
					num[to] = v;
					if (!dfs(to))
						return 0;
				}
			}
		}
		return 1;
	}

	int count(vector<string> board)
	{
		G = board;
		n = board.size();

		int ans = 1, ans_0 = 1;
		memset(vis, 0, sizeof(vis));

		for (int i = 0; i < n; ++i) if (!vis[i])
		{
			int cnt = 0, cnt_0 = 0;
			rep (j, 0, 9)
			{
				memset(num, -1, sizeof(num));
				num[i] = j;
				if (dfs(i))
				{
					cnt += 1;
					cnt_0 += std::count(num, num + n, 0) == 0;
				}
			}
			ans = (LL) ans * cnt % mo;
			ans_0 = (LL) ans_0 * cnt_0 % mo;
		}

		return (ans - ans_0 + mo) % mo;
	}
};
