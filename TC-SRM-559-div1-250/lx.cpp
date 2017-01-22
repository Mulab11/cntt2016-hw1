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

class HyperKnight
{
public : 
	LL countCells(int a, int b, int R, int C, int K)
	{
		if (a < b)
			swap(a, b);

		static LL r[9];

		r[2] = 4ll * b * b;
		r[3] = 8ll * (a - b) * b;
		r[6] = 2ll * (a - b) * (C + R - 4 * a);
		r[8] = 1ll * (R - 2 * a) * (C - 2 * a);
		r[4] = 1ll * R * C - r[2] - r[3] - r[6] - r[8];

		return r[K];
	}
};
