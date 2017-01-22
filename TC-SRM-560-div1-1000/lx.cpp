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

const int inf = 0x3f3f3f3f;
const int N = 13;

class BoundedOptimization
{
public : 
	int n;
	bool adj[N][N];

	double maxValue(vector<string> expr, vector<int> Low, vector<int> Up, int maxSum)
	{
		n = Low.size();

		string str = "";
		rep (i, 0, expr.size() - 1)
			str += expr[i];

		for (int i = 0; i < str.size(); i += 3)
		{
			int x = str[i] - 'a';
			int y = str[i + 1] - 'a';
			adj[x][y] = adj[y][x] = 1;
		}

		int tot = (1 << n) - 1;
		double ans = 0;

		rep (S, 0, tot)
		{
			static int sta[N], cur;
			cur = 0;
			rep (i, 0, n - 1)
			{
				if ((S >> i) & 1)
					sta[cur++] = i;
			}
			bool flag = 1;
			rep (i, 0, cur - 1) rep (j, i + 1, cur - 1)
			{
				if (!adj[sta[i]][sta[j]])
					flag = 0;
			}
			if (!flag)
				continue ;
			int other = tot ^ S, T = other;
			do
			{
				static double val[N];
				memset(val, 0, sizeof(val));

				double M = maxSum;

				rep (i, 0, n - 1)
				{
					if (((T >> i) & 1) == 1)
						val[i] = Up[i];
					else if (((other >> i) & 1) == 1)
						val[i] = Low[i];
					M -= val[i];
				}

				if (M >= 0)
				{
					double sum = 0;
					rep (i, 0, cur - 1)
					{
						int u = sta[i];
						double a = 0;
						rep (j, 0, n - 1)
						{
							if (adj[u][j] && ((other >> j) & 1) == 1)
								a += val[j];
						}
						val[u] = a + M / 2;
						sum += val[u];
					}
					double c = (M - sum) / cur;
					bool can = 1;
					rep (i, 0, cur - 1)
					{
						int u = sta[i];
						val[u] += c;
						if (val[u] < Low[u] + 1e-9 || val[u] > Up[u] + 1e-9)
							can = 0;
					}
					if (can)
					{
						double now = 0;
						rep (i, 0, n - 1) rep (j, i + 1, n - 1)
						{
							if (adj[i][j])
								now += val[i] * val[j];
						}
						upmax(ans, now);
					}
				}

				T = (T - 1) & other;
			} 
			while (T != other);
		}

		return ans;
	}
};

