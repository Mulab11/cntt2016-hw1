#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;

class TomekPhone
{
public : 
	int minKeystrokes(vector<int> num, vector<int> cnt)
	{
		vector<int> cost;
		rep (i, 0, cnt.size() - 1)
		{
			rep (j, 1, cnt[i])
				cost.pb(j);
		}
		if (cost.size() < num.size()) 
			return -1;

		sort(cost.begin(), cost.end());
		sort(num.begin(), num.end());

		int cur = 0, ans = 0;

		down (i, num.size() - 1, 0)
			ans += cost[cur++] * num[i];

		return ans;
	}
};
