#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

int map[110][110];
int ret[110][3];

class PastingPaintingDivOne
{
public:
	vector<ll> countColors(vector<string> inp, int T)
	{
		int N = inp.size(), M = inp[0].size();
		memset(map, -1, sizeof map);
		vector<ll> ans(3, 0ll);
		for(int k = 1; k <= 50; ++k)
		{
			for(int i = 0; i != N; ++i)
				for(int j = 0; j != M; ++j)
					switch(inp[i][j])
				{
					case 'R':	map[k + i][k + j] = 0; break;
					case 'G':	map[k + i][k + j] = 1; break;
					case 'B':	map[k + i][k + j] = 2; break;
				}
			for(int i = 0; i <= 100; ++i)
				for(int j = 0; j <= 100; ++j)
					if(map[i][j] != -1)
						++ret[k][map[i][j]];
			if(!--T) return vector<ll>(ret[k], ret[k] + 3);
		}
		for(int i = 0; i != 3; ++i)
			ans[i] = (ll) T * (ret[50][i] - ret[49][i]) + ret[50][i];
		return ans;
	}
}	user;
