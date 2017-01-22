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
const LL inf = 0x3f3f3f3f3f3f3f3f;

class SkiResorts
{
public :
	vector<int> H;
	int id[55][55], n, m, tot;
	pii loc[2711];
	LL dis[2711];
	bool vis[2711];

	LL minCost(vector<string> board, vector<int> altitude)
	{
		n = altitude.size();
		H = altitude;
		sort(H.begin(), H.end());
		H.erase(unique(H.begin(), H.end()), H.end());
		m = H.size();

		rep (i, 0, n - 1) rep (j, 0, m - 1)
		{
			loc[tot] = mp(i, j);
			id[i][j] = tot++;
		}

		memset(vis, 0, sizeof(vis));
		memset(dis, 0x3f, sizeof(dis));
		rep (i, 0, m - 1)
			dis[id[0][i]] = abs(H[i] - altitude[0]);

		rep (i, 0, tot - 1)
		{
			int u = -1;
			rep (i, 0, tot - 1) 
			{
				if (!vis[i] && (u == -1 || dis[i] < dis[u]))
					u = i;
			}
			vis[u] = 1;
			pii o = loc[u];
			rep (i, 0, n - 1) 
			{
				if (board[o.x][i] == 'Y')
				{
					rep (j, 0, o.y)
						upmin(dis[id[i][j]], dis[u] + abs(altitude[i] - H[j]));
				}
			}
		}

		LL ans = inf;
		rep (i, 0, m - 1)
			upmin(ans, dis[id[n - 1][i]]);
		return ans < inf ? ans : -1;
	}
};
