#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }

class SpellCards
{
public : 
	int maxDamage(vector<int > lev, vector<int > dm)
	{
		static int f[55];
		memset(f, 0, sizeof(f));
		int n = lev.size();
		rep (i, 0, n - 1)
		{
			down (j, n - lev[i], 0)
				upmax(f[j + lev[i]], f[j] + dm[i]);
		}
		int ans = 0;
		rep (i, 0, n)
			upmax(ans, f[i]);
		return ans;
	}
};
