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

typedef pair<int , int > pii;

class MagicMolecule
{
public : 
	vector<int> val;
	vector<pii> lim;
	bool vis[55];
	int n, ans;

	void search(int now, int rest)
	{
		if (now == lim.size())
		{
			int tmp = 0;
			rep (i, 0, n - 1)
			{
				if (vis[i])
					tmp += val[i];
			}
			upmax(ans, tmp);
		}
		else
		{
			pii u = lim[now];
			if (!vis[u.x] || !vis[u.y])
				search(now + 1, rest);
			else if (rest > 0)
			{
				vis[u.x] = 0;
				search(now + 1, rest - 1);
				vis[u.x] = 1;
				vis[u.y] = 0;
				search(now + 1, rest - 1);
				vis[u.y] = 1;
			}
		}
	}

	int maxMagicPower(vector<int> val, vector<string> bonds)
	{
		this->val = val;
		n = val.size();
		rep (i, 0, n - 1) rep (j, i + 1, n - 1)
		{
			if (bonds[i][j] == 'N')
				lim.pb(mp(i, j));
		}
		memset(vis, 1, sizeof(vis));
		ans = -1;
		int dnum = n - (n * 2 + 2) / 3;
		search(0, dnum);
		return ans;
	}
};
