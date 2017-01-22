#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 7;
const int N = 1e5 + 10;

inline void upd(int & x, int y)
{
	(x += y) >= mo ? x -= mo : 0;
}

struct poly
{
	int a[353];
	inline int operator [](const int x) const
	{
		return a[x];
	}
	inline int & operator [] (const int x)
	{
		return a[x];
	}
};

class PenguineEmperor
{
public :
	int n;

	poly mul(const poly & a, const poly & b)
	{
		static poly ans;
		rep (i, 0, n - 1)
		{
			ans[i] = 0;
			rep (j, 0, n - 1)
				upd(ans[i], (LL) a[j] * b[(i - j + n) % n] % mo);
		}
		return ans;
	}

	int countJourneys(int n, LL m)
	{
		this->n = n;
		int b = m % n;
		m /= n;

		poly step = {0};
		poly tmp = {0};
		poly ans = {0};

		step[0] = 1;

		rep (i, 1, n - 1)
		{
			tmp[i] = tmp[n - i] = 1;
			step = mul(step, tmp);
			if (i == b)
				ans = step;
			tmp[i] = tmp[n - i] = 0;
		}

		if (!b)
			ans[0] = 1;

		while (m)
		{
			if (m & 1)
				ans = mul(ans, step);
			step = mul(step, step);
			m >>= 1;
		}

		return ans[0];
	}
};
