#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<int> e[60];

class TravelOnMars
{
public:
	int minTimes(vector<int> ran, int s, int t)
	{
		int n = ran.size();
		for(int i = 0; i != n; ++i)
		{
			int R = ran[i];
			for(int k = 0; k != n; ++k)
				if(min((i - k + n) % n, (k - i + n) % n) <= R)
					e[i].push_back(k);
		}
		static int q[60], d[60];
		memset(d, -1, n << 2);
		int l = 0, r = 0; d[q[r++] = s] = 0;
		while(l != r)
		{
			int p = q[l++], D = d[p];
			for(int k = e[p].size(); k--; )
				if(d[e[p][k]] == -1)
					d[q[r++] = e[p][k]] = D + 1;
		}
		return d[t];
	}
}	user;
