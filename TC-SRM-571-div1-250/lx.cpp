#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

class FoxAndMp3
{
public :
	vector<string> playList(int n)
	{
		vector<string> ans;
		int x = 1;
		rep (i, 1, min(n, 50))
		{
			ans.pb(to_string(x) + ".mp3");
			if ((LL) x * 10 <= n)
				x *= 10;
			else
			{
				while (x == n || x % 10 == 9)
					x /= 10;
				++x;
			}
		}
		return ans;
	}
};
