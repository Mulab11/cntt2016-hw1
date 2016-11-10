#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

vector<int> e[60];
bool v[60];
int dp(int i)
{
	v[i] = 1;
	int deg = 0, ans = 0, cnt = 0;
	for(int k = 0; k != (int) e[i].size(); ++k)
		if(!v[e[i][k]])
		{
			int tmp = dp(e[i][k]);
			ans += tmp;
			++deg;
			if(tmp) ++cnt;
		}
	v[i] = 0;
	// 如果是链，则不需要有关键点
	// 最多有 1 个分支没有关键点
	// 因此把没有关键点的分支强行补一个 1
	return ans + max(0, deg - 1 - cnt);
}

class TPS
{
public:
	int minimalBeacons(vector<string> edge)
	{
		if(edge.size() == 1u) return 0;
		const int N = edge.size();
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != N; ++j)
				if(edge[i][j] == 'Y')
					e[i].push_back(j);
		int ans = 100000;
		for(int i = 0; i != N; ++i) ans = min(ans, dp(i) + 1);
		return ans;
	}
}	user;
