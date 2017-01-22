#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class XorAndSum
{
public :
	LL bin[65];
	LL base[65];

	LL maxSum(vector<LL> num)
	{
		bin[0] = 1;
		rep (i, 1, 63)
			bin[i] = bin[i - 1] << 1;
		int n = num.size(), tot = 0;
		rep (i, 0, n - 1)
		{
			LL v = num[i];
			down (j, 62, 0) 
			{
				if (v & bin[j])
				{
					if (base[j])
						v ^= base[j];
					else
					{
						base[j] = v;
						break ;
					}
				}
			}
			if (!v)
				++tot;
		}
		LL now = 0;
		down (i, 62, 0) 
			upmax(now, now ^ base[i]);
		LL ans = now * tot;
		rep (i, 0, 62)
		{
			if (base[i])
			{
				rep (j, i + 1, 62)
				{
					if (base[j] & bin[i])
						base[j] ^= base[i];
				}
			}
		}
		down (i, 62, 0)
		{
			if (base[i])
			{
				down (j, i - 1, 0)
					base[i] ^= base[j];
				ans += base[i];
				down (j, i - 1, 0)
				{
					if (base[j])
						ans += base[j] ^ base[i];
				}
				break ;
			}
		}
		return ans;
	}
};
