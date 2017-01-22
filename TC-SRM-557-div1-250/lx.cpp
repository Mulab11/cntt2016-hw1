#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class FoxAndMountainEasy
{
public : 
	string possible(int n, int h0, int hn, string his)
	{
		int m = his.size();
		int mi = 0, d = 0;
		rep (i, 0, m - 1)
		{
			d += his[i] == 'U' ? 1 : -1;
			upmin(mi, d);
		}
		int x = h0 + d, v = abs(hn - x);
		if (v < n - m || v % 2 != (n - m) % 2)
			return "NO";
		int up = (n - m + hn - x) / 2;
		if (h0 + up + mi < 0)
			return "NO";
		return "YES";
	}
};
