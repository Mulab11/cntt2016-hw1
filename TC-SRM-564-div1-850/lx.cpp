#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)

using namespace std;
typedef long long LL;

const int mo = 1e9 + 7;

class DefectiveAddition
{
public : 
	int bin[33];

	inline void upd(int & x, int y)
	{
		(x += y) >= mo ? x -= mo : 0;
	}

	int count(vector<int> cards, int w)
	{
		int n = cards.size();
		int ans = 0;

		bin[0] = 1;
		rep (i, 1, 31)
			bin[i] = bin[i - 1] << 1;

		down (i, 30, 0)
		{
			int flag = (w >> i) & 1;
			int tmp = 0;
			int now = 1;
			rep (j, 0, n - 1)
			{
				if (cards[j] & bin[i])
				{
					int f[2] = {0};
					f[tmp] = now;

					rep (k, j + 1, n - 1)
					{
						LL x = f[0], y = f[1];
						int v = (cards[k] >> i) & 1;
						f[0] = f[1] = 0;
						if (v)
						{
							upd(f[1], x * (cards[k] - bin[i] + 1) % mo);
							upd(f[0], x * bin[i] % mo);
							upd(f[0], y * (cards[k] - bin[i] + 1) % mo);
							upd(f[1], y * bin[i] % mo);
						}
						else
						{
							upd(f[0], x * (cards[k] + 1) % mo);
							upd(f[1], y * (cards[k] + 1) % mo);
						}
					}

					cards[j] ^= bin[i];
					tmp ^= 1;

					upd(ans, f[flag]);
				}

				now = (LL) now * (cards[j] + 1) % mo;
			}
			if (tmp != flag)
				break ;
			else if (i == 0)
				++ans;
			if (flag)
				w ^= bin[i];
		}

		return ans;
	}
};
