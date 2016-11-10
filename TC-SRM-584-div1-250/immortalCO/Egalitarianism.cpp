#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

int d[60][60];
class Egalitarianism
{
public:
	int maxDifference(vector<string> map, int lim)
	{
		memset(d, 63, sizeof d);
		int N = map.size();
		for(int i = 0; i != N; ++i)
		{
			d[i][i] = 0;
			for(int j = 0; j != N; ++j)
				if(map[i][j] == 'Y') d[i][j] = 1;
		}
		for(int k = 0; k != N; ++k)
			for(int i = 0; i != N; ++i)
				for(int j = 0; j != N; ++j)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		int M = 0;
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != N; ++j)
				if(d[i][j] > 1e9) return -1;
				else M = max(M, d[i][j]);
		return M * lim;
	}
}	user;
