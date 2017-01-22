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

void decode(vector<int> & A, const vector<string> & B)
{
	stringstream V;
	rep (i, 0, B.size() - 1)
		V << B[i];
	int x;
	while (V >> x)
		A.pb(x);
}

class Ear
{
public : 
	LL getCount(vector<string> in_1, vector<string> in_2, vector<string> in_3)
	{
		vector<int> R, Bx, By;
		decode(R, in_1);
		decode(Bx, in_2);
		decode(By, in_3);

		sort(R.begin(), R.end());
		int n = R.size(), m = Bx.size();
		LL ans = 0;

		rep (i, 0, m - 1) rep (j, 0, m - 1)
		{
			if (By[i] <= By[j])
				continue ;

			int num1, num2, lim, x, y;
			int mx = Bx[i], mi = Bx[j];

			if (mx < mi)
				swap(mx, mi);

			double tmp = Bx[j] - (double) By[j] * (Bx[i] - Bx[j]) / (By[i] - By[j]);

			lim = Bx[j];
			for (x = 0; x < n && R[x] < lim; ++x) ;
			lim = min(mi, int(ceil(tmp)));
			for (y = 0; y < x && R[y] < lim; ++y) ;
			num1 = y * (x * 2 - y - 1) / 2;

			lim = Bx[j];
			for (x = n - 1; x >= 0 && R[x] > lim; --x) ;
			lim = max(mx, int(floor(tmp)));
			for (y = n - 1; y > x && R[y] > lim; --y) ;
			x = n - x - 1;
			y = n - y - 1;
			num2 = y * (x * 2 - y - 1) / 2;

			ans += (LL) num1 * num2;
		}

		return ans;
	}
};
