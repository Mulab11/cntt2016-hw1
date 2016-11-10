#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

class CheckerExpansion
{
public:
	vector<string> resultAfter(ll t, ll X, ll Y, int n, int m)
	{
		--t;
		vector<string> ret(m, string(n, '.'));
		for(int i = 0; i != m; ++i)
		{
			for(int j = 0; j != n; ++j)
			{
				ll x = X + j;
				ll y = Y + m - i - 1;
				if((x + y) % 2 == 0 && (x + y) / 2 <= t && 0 <= y && y <= (x + y) / 2 && (~((x + y) / 2) & y) == 0)
					ret[i][j] = "AB"[(x + y) / 2 % 2];
			}
		}
		return ret;
	}
}	user;
