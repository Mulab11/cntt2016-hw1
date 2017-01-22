#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int N = 53;

class LeftRightDigitsGame2
{
public :
	string dig, bound;
	bool vis[N][N][2];
	string dp[N][N][2];
	int n;

	inline int cmp(int x, int y, int t)
	{
		while (t--)
		{
			if (dig[x] > bound[y])
				return 1;
			else if (dig[x] < bound[y])
				return -1;
			++x, ++y;
		}
		return 0;
	}

	string calc(int cnt, int start, bool f)
	{
		if (vis[cnt][start][f])
			return dp[cnt][start][f];

		vis[cnt][start][f] = 1;
		string & v = dp[cnt][start][f];

		if (cmp(0, start, cnt) >= f)
			v = dig.substr(0, cnt);

		rep (i, 1, cnt - 1)
		{
			if (v.size() && dig[i] > v[0])
				continue ;
			if (dig[i] >= bound[start])
			{
				int rest = cnt - i - 1;
				string t;

				if (dig[i] > bound[start])
				{
					t = dig.substr(i, 1);
					string back = dig.substr(i + 1, rest);
					int cur = i - 1;
					while (cur >= 0)
					{
						int best = cur;
						down (j, cur - 1, 0)
						{
							if (dig[j] < dig[best])
								best = j;
						}
						t += dig.substr(best, 1);
						if (cur > best)
							back = dig.substr(best + 1, cur - best) + back;
						cur = best - 1;
					}
					t += back;
				}
				else
				{
					bool flag = cmp(i + 1, start + i + 1, rest) < f;
					t = calc(i, start + 1, flag);
					if (t.size())
						t = dig.substr(i, 1) + t + dig.substr(i + 1, rest);
					else
						continue ;
				}
				if (!v.size() || t < v)
					v = t;
			}
		}

		return v;
	}

	string minNumber(string dig, string bound)
	{
		this->dig = dig;
		this->bound = bound;
		n = dig.size();
		string ans = calc(n, 0, 0);
		return ans;
	}
};
