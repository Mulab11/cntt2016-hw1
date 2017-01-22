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

class MapGuessing
{
public : 
	bool vis[36];
	char be[36];
	int n, m;

	LL calc(string & goal, string & code, int pos)
	{
		memset(vis, 0, sizeof(vis));
		LL ans = 0;
		rep (i, 0, m - 1)
		{
			if (code[i] == '0' || code[i] == '1')
			{
				be[pos] = code[i];
				vis[pos] = 1;
			}
			else
				code[i] == '<' ? --pos : ++pos;
			int j = 0;
			LL now = 0;
			for ( ; j < n; ++j)
			{
				if (vis[j])
				{
					if (be[j] == goal[j])
						now ^= 1ll << j;
					else
						break ;
				}
			}
			if (j == n)
				ans = now;
		}
		return ans;
	}

	LL get(LL v)
	{
		LL ans = 1;
		while (v)
		{
			ans <<= 1;
			v -= v & -v;
		}
		return ans;
	}

	LL countPatterns(string goal, vector<string> codes)
	{
		string code = "";
		rep (i, 0, codes.size() - 1)
			code += codes[i];
		n = goal.size();
		m = code.size();

		int pos = 0, lm = 0, rm = 0;
		rep (i, 0, m - 1)
		{
			if (code[i] == '<')
			  --pos;
			else if (code[i] == '>')
			  ++pos;
			upmin(lm, pos);
			upmax(rm, pos);
		}

		lm = -lm;
		int vol = lm + rm;

		if (vol >= n)
			return 0;

		vector<LL> num;
		rep (i, lm, n - rm - 1)
			num.pb(calc(goal, code, i));

		LL ans = 1;
		rep (i, 0, num.size() - 1)
		{
			int vv = min(int(num.size() - i - 1), vol);
			rep (j, 0, (1 << vv) - 1)
			{
				int cnt = 1;
				LL mask = num[i];
				rep (k, 0, vv - 1)
				{
					if (j & (1 << k))
					{
						++cnt;
						mask &= num[i + 1 + k];
					}
				}
				LL tmp = get(mask) - 1;
				cnt & 1 ? ans += tmp : ans -= tmp;
			}
		}

		return ans;
	}
};
