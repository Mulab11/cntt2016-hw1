#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
#define to first
#define len second
vector< pair<int, int> > e[60];

class ColorfulWolves
{
public:
	int getmin(vector<string> mp)
	{
		n = mp.size();
		for(int i = 0; i != n; ++i)
		{
			int cost = 0;
			for(int j = 0; j != n; ++j) if(mp[i][j] == 'Y')
				e[i].push_back(make_pair(j, cost++));
		}
		static int q[60], d[60];
		static bool v[60];
		int l = 0, r = 0;
		v[q[r++] = 0] = 1;
		memset(d, 63, n << 2);
		d[0] = 0;
		while(l != r)
		{
			int p = q[l++], D = d[p]; v[p] = 0;
			vector<pair<int, int> > &e = ::e[p];
			for(int i = 0; i != (int) e.size(); ++i)
				if(d[e[i].to] > D + e[i].len)
				{
					d[e[i].to] = D + e[i].len;
					if(!v[e[i].to])
						v[q[r++] = e[i].to] = 1;
				}
		}
		return d[n - 1] > 1e9 ? -1 : d[n - 1];
	}
}	user;
