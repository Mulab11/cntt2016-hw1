#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;

class CuttingBitString
{
public : 
	int f[55];

	int can(string s)
	{
		if (s[0] == '0')
			return 0;
		LL t = 0;
		rep (i, 0, s.size() - 1)
			t = t << 1 | (s[i] - '0');
		while (t % 5 == 0)
			t /= 5;
		return t == 1;
	}

	int getmin(string S)
	{
		int n = S.size();
		rep (i, 1, n)
		{
			if (can(S.substr(0, i)))
			{
				f[i] = 1;
				continue ;
			}
			f[i] = inf;
			rep (j, 1, i - 1)
			{
				if (f[j] < f[i] - 1 && can(S.substr(j, i - j)))
					f[i] = f[j] + 1;
			}
		}
		return f[n] < inf ? f[n] : -1;
	}
};
