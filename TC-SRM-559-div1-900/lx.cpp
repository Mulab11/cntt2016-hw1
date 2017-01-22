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

const double Pi = acos(-1);
const int N = 52;

class CircusTents
{
public :
	int dx[N], dy[N], r[N], n;
	double d[N], theta[N];

	inline double adjust(double x)
	{
		while (x < 0)
			x += Pi * 2.0;
		while (x > Pi * 2.0)
			x -= Pi * 2.0;
		return x;
	}

	inline double dis(double r1, double r2, double d, double x)
	{
		if (x > Pi)
			x = 2.0 * Pi - x;
		double bound = acos(r1 / d);
		if (x <= bound)
		{
			double dx = d - r1 * cos(x), dy = r1 * sin(x);
			return sqrt(dx * dx + dy * dy) - r2;
		}
		return d * sin(bound) - r2 + r1 * (x - bound);
	}

	bool check(double D)
	{
		vector<double> ang;

		ang.pb(0);
		ang.pb(2.0 * Pi);

		rep (i, 1, n - 1)
		{
			if (dis(r[0], r[i], d[i], Pi) < D)
				return 1;
			if (dis(r[0], r[i], d[i], 0) > D)
				continue ;
			double low = 0.0, high = Pi;
			rep (j, 1, 100)
			{
				double mid = (low + high) / 2.0;
				dis(r[0], r[i], d[i], mid) > D ? high = mid : low = mid;
			}
			ang.pb(adjust(theta[i] + high));
			ang.pb(adjust(theta[i] - high));
		}

		sort(ang.begin(), ang.end());

		rep (i, 0, ang.size() - 2)
		{
			bool flag = 0;
			rep (j, 1, n - 1)
			{
				double tmp = adjust((ang[i] + ang[i + 1]) / 2.0 - theta[j]);
				if (dis(r[0], r[j], d[j], tmp) < D)
				{
					flag = 1;
					break ;
				}
			}
			if (!flag)
				return 0;
		}

		return 1;
	}

	double findMaximumDistance(vector<int> x, vector<int> y, vector<int> r)
	{
		n = x.size();
		this->r[0] = r[0];

		rep (i, 1, n - 1)
		{
			dx[i] = x[i] - x[0];
			dy[i] = y[i] - y[0];
			d[i] = sqrt(dx[i] * dx[i] + dy[i] * dy[i]);
			this->r[i] = r[i];
			theta[i] = atan2(dy[i], dx[i]);
		}

		double low = 0, high = 1000000;

		rep (i, 1, 100)
		{
			double mid = (low + high) / 2.0;
			check(mid) ? high = mid : low = mid;
		}

		return high;
	}
};

