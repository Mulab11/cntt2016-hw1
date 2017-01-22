#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 9;
const int N = 63;

class UnknownTree
{
public :
	int calc_one(vector<int > d)
	{
		LL ans = 1;
		rep (i, 0, d.size() - 1)
		{
			int cnt = 1;
			rep (j, 0, d.size() - 1) 
				cnt += d[j] < d[i];
			ans = ans * cnt % mo;
		}
		return ans;
	}

	int calc_two(vector<pair<int, int> > nodes)
	{
		int n = nodes.size();
		sort(nodes.begin(), nodes.end());

		static vector<int> G[N];
		static vector<pair<int , int> > S;

		S.clear();
		G[0].clear();
		S.pb(nodes[0]);

		int cn = 1;

		rep (i, 1, n - 1)
		{
			bool flag = 1;
			int l = nodes[i].x, r = nodes[i].y;
			rep (j, 0, cn - 1)
			{
				int dl = l - S[j].x;
				int dr = r - S[j].y;
				if (dl == 0)
					return 0;
				if (dl == dr)
				{
					G[j].pb(dl);
					flag = 0;
					break ;
				}
			}
			if (flag)
			{
				if (l + r - nodes[0].y != 0)
					return 0;
				G[cn].clear();
				S.pb(nodes[i]);
				cn++;
			}
		}

		LL ans = 1;

		rep (i, 0, cn - 1)
			ans = ans * calc_one(G[i]) % mo;

		return ans;
	}
    
	int count_L(vector<int> & Ad, vector<int> & Bd, vector<int> & Cd)
	{
        set<pair<int,int> > my;
		int n = Ad.size();

		rep (i, 0, n - 1)
		{
			int x, y;

			x = Ad[i] - Cd[i];
			y = Bd[i] - Cd[i];
			if (x > 0 && y > 0)
				my.insert(mp(x, y));

			x = Ad[i] + Cd[i];
			y = Bd[i] - Cd[i];
			if (x > 0 && y > 0)
				my.insert(mp(x, y));

			x = Cd[i] - Ad[i];
			if (x > 0 && y > 0)
				my.insert(mp(x, y));

			x = Ad[i] - Cd[i];
			y = Bd[i] + Cd[i];
			if (x > 0)
				my.insert(mp(x, y));

			y = Cd[i] - Bd[i];
			if (x > 0 && y > 0)
				my.insert(mp(x, y));
		}

		LL ans = 0;

		for (set<pair<int, int> > :: iterator it = my.begin(); it != my.end(); it++)
		{
			int x = it->x;
			int y = it->y;
			vector<pair<int, int> > inA, inB;
			vector<int> other;

			inA.pb(mp(0, x));
			inA.pb(mp(x, 0));
			inB.pb(mp(0, y));
			inB.pb(mp(y, 0));

			bool can = 1;
			for (int i = 0; i < n && can; ++i)
			{
				int dc = Cd[i];
				int da = Ad[i] - x;
				int db = Bd[i] - y;
				if (dc == da && dc == db)
					other.pb(dc);
				else if (dc == db)
					inA.pb(mp(Ad[i], dc));
				else if (dc == da)
					inB.pb(mp(Bd[i], dc));
				else 
					can = 0;
			}

			if (can)
			{
				LL tmp = (LL) calc_two(inA) * calc_two(inB) % mo * calc_one(other) % mo;
				ans += tmp;
			}
		}

		return ans % mo;
    }
    
	int count_Y(vector<int> & Ad, vector<int> & Bd, vector<int> & Cd, int c)
	{
		int n = Ad.size();
		vector<pair<int , int > > inA, inB, inC;
		vector<int> other;

		inA.pb(mp(0, Ad[c]));
		inA.pb(mp(Ad[c], 0));
		inB.pb(mp(0, Bd[c]));
		inB.pb(mp(Bd[c], 0));
		inC.pb(mp(0, Cd[c]));
		inC.pb(mp(Cd[c], 0));

		rep (i, 0, n - 1) if (i != c)
		{
			int da = Ad[i] - Ad[c];
			int db = Bd[i] - Bd[c];
			int dc = Cd[i] - Cd[c];
			if (da > 0 && da == db && da == dc)
				other.pb(da);
			else if (db > 0 && db == dc)
				inA.pb(mp(db, Ad[i]));
			else if (da > 0 && da == dc)
				inB.pb(mp(da, Bd[i]));
			else if (da > 0 && da == db)
				inC.pb(mp(da, Cd[i]));
			else 
				return 0;
		}

		LL ans = (LL) calc_two(inA) * calc_two(inB) % mo * calc_two(inC) % mo * calc_one(other) % mo;
		return ans;
	}

	int getCount(vector<int> Ad, vector<int> Bd, vector<int> Cd)
	{
		int n = Ad.size();
		LL ans = 0;

		rep (i, 0, n - 1)
			ans += count_Y(Ad, Bd, Cd, i);

		ans += count_L(Ad, Bd, Cd);
		ans += count_L(Bd, Cd, Ad);
		ans += count_L(Cd, Ad, Bd);

		return ans % mo;
	}
};

