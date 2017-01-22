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

const int N = 1e6 + 10;

class TheDivisionGame
{
public :
	bool vis[N];
	int now[N], cnt[N];
	int num[55];

	LL countWinningIntervals(int L, int R)
	{
		int n = R - L + 1;
		int m = sqrt(R);

		rep (i, L, R)
			now[i - L] = i;

		rep (i, 2, m)
		{
			if (vis[i])
				continue ;
			int s = L + (i - 1 - (L - 1) % i);
			while (s <= R)
			{
				while (now[s - L] % i == 0)
				{
					now[s - L] /= i;
					cnt[s - L]++;
				}
				s += i;
			}
			for (int j = i; j <= m; j += i)
				vis[j] = 1;
		}

		rep (i, 0, n - 1)
			cnt[i] += now[i] > 1;

		LL ans = (LL) n * (n + 1) >> 1;
		int s = 0;

		num[0] = 1;

		rep (i, 0, n - 1)
		{
			s ^= cnt[i];
			ans -= num[s]++;
		}

		return ans;
	}
};
