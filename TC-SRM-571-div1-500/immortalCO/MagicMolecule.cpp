#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int N, L, p[60], v[60];
ll e[60];
int ans = -1;

bool cmp(int x, int y) {return v[x] > v[y];}

inline int value(ll S)
{
	int ret = 0;
	for(int k; S; S -= 1ll << k)
		ret += v[k = __builtin_ctzll(S)];
	return ret;
}

void dfs(int c, int s, ll S)
{
	if(c >= L && s > ans) ans = s;
	if(!S || c + __builtin_popcountll(S) < L || s + value(S) <= ans) return;
	for(int i; S; S -= 1ll << i)
	{
		i = __builtin_ctzll(S);
		dfs(c + 1, s + v[i], S & e[i]);
	}
}

class MagicMolecule
{
public:
	int maxMagicPower(vector<int> val, vector<string> map)
	{
		N = val.size();
		L = (2 * N + 2) / 3;
		for(int i = 0; i != N; ++i) v[i] = val[i], p[i] = i;
		sort(p, p + N, cmp);
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != N; ++j)
				if(map[p[i]][p[j]] == 'Y')
					e[i] |= 1ll << j;
		sort(v, v + N, greater<int>());
		dfs(0, 0, (1ll << N) - 1);
		return ans;
	}
}	user;
