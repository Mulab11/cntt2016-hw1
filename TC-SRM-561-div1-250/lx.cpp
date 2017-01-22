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
const int N = 105;

class ICPCBalloons
{
public : 
	int num[N];
	int Mc[N], cm;
	int Lc[N], cl;
	int n, m;

	int calc(int S)
	{
		static int a[N], ca;
		static int b[N], cb;
		ca = cb = 0;
		rep (i, 0, m - 1) 
		{
			if ((S >> i) & 1)
				a[ca++] = num[i];
			else
				b[cb++] = num[i];
		}

		sort(a, a + ca);
		sort(b, b + cb);

		int ans = 0;
		int cur = cm - 1, tmp = 0;

		down (i, ca - 1, 0)
		{
			if (cur < 0)
			{
				ans += a[i];
				tmp -= a[i];
			}
			else
			{
				ans += max(a[i] - Mc[cur], 0);
				tmp += Mc[cur] - a[i];
				cur--;
			}
		}
		while (cur >= 0)
			tmp += Mc[cur--];

		if (tmp < 0)
			return inf;

		cur = cl - 1, tmp = 0;

		down (i, cb - 1, 0)
		{
			if (cur < 0)
			{
				ans += b[i];
				tmp -= b[i];
			}
			else
			{
				ans += max(b[i] - Lc[cur], 0);
				tmp += Lc[cur] - b[i];
				cur--;
			}
		}
		while (cur >= 0)
			tmp += Lc[cur--];

		if (tmp < 0)
			return inf;

		return ans;
	}

	int minRepaintings(vector<int> Count, string col, vector<int> num)
	{
		n = Count.size();
		cm = cl = 0;
		rep (i, 0, n - 1)
		{
			if (col[i] == 'M')
				Mc[cm++] = Count[i];
			else
				Lc[cl++] = Count[i];
		}

		sort(Mc, Mc + cm);
		sort(Lc, Lc + cl);

		int ans = inf;
		m = num.size();

		rep (i, 0, m - 1)
			this->num[i] = num[i];

		rep (s, 0, (1 << m) - 1)
			upmin(ans, calc(s));

		return ans < inf ? ans : -1;
	}
};

