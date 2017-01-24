#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second

using namespace std;
typedef long long LL;

template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;

class BallsSeparating
{
public:
	int minOperations(vector <int> red, vector <int> green, vector <int> blue)
	{
		int ans = inf;
		int n = red.size();

		for (int r = 0; r < n; ++r) 
		{
			for (int g = 0; g < n; ++g) if (g != r)
			{
				for (int b = 0; b < n; ++b) if (b != g && b != r)
				{
					int cost = 0;
					for (int i = 0; i < n; ++i)
					{
						int m_r = blue[i] + green[i];
						int m_b = red[i] + green[i];
						int m_g = red[i] + blue[i];
						if (i == r)
							cost += m_r;
						else if (i == g)
							cost += m_g;
						else if (i == b)
							cost += m_b;
						else
							cost += min(min(m_r, m_b), m_g);
					}
					upmin(ans, cost);
				}
			}
		}

		return ans < inf ? ans : -1;
	}
};
