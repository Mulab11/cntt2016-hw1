#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class MonstersValley
{
public :
	LL f[105];

	int minimumPrice(vector<LL> A, vector<int > B)
	{
		int n = A.size();
		rep (i, 0, n - 1)
		{
			LL x = A[i];
			int y = B[i];
			down (j, 100, 0) 
			{
				if (f[j] >= 0)
					upmax(f[j + y], f[j] + x);
				if (f[j] < x)
					f[j] = -1;
			}
		}
		int cur = 0;
		while (f[cur] < 0)
			++cur;
		return cur;
	}
} my;

