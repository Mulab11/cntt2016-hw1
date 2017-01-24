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

const int N = 53;

class PenguinSledding
{
public :
	int deg[N];
	int w[N][N];

	LL countDesigns(int n, vector<int > left, vector<int > right)
	{
		LL ans = 1 + left.size();

		rep (i, 0, left.size() - 1)
		{
			int x = left[i], y = right[i];
			w[x][y] = w[y][x] = 1;
			deg[x]++;
			deg[y]++;
		}

		rep (i, 1, n)
			ans += (1ll << deg[i]) - deg[i] - 1;

		rep (i, 1, n) rep (j, i + 1, n) rep (k, j + 1, n)
		{
			if (w[i][j] && w[j][k] && w[k][i])
				++ans;
		}

		return ans;
	}
};
