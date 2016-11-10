#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<int> e[60];
ll cur;
int c[60], m, l;
void dfs(int i, int d, int f)
{
	++c[d];
	m = max(m, d);
	int s = 0;
	for(int k = 0; k != (int) e[i].size(); ++k)
	{
		if(e[i][k] == f) continue;
		if(++s > 2) {cur = 0; return;}
		dfs(e[i][k], d + 1, i);
	}
}
int calc(int i, int d, int f)
{
	if(d == m) return 1;
	int s = 0, c = 0, v = 0;
	for(int k = 0; k != (int) e[i].size(); ++k)
		if(e[i][k] != f)
		{
			++c;
			int t = calc(e[i][k], d + 1, i);
			s += t;
			v += (!t || t == (1 << (m - d - 1)));
		}
	if(c == 2)
	{
		if(!v) cur = 0;
		if(!s || s == (1 << (m - d))) cur <<= 1;
	}
	if(d + 1 == m && c == 1) ++l;
	return s;
}

class HatRack
{
public:
	ll countWays(vector<int> a, vector<int> b)
	{
		int n = a.size() + 1;
		for(int i = 0; i + 1 != n; ++i)
		{
			e[a[i]].push_back(b[i]),
			e[b[i]].push_back(a[i]);
		}
		ll ans = 0;
		for(int r = 1; r <= n; ++r)
		{
			cur = 1;
			m = 0;
			dfs(r, 0, -1);
			for(int i = 0; i != m; ++i)
				if(c[i] != (1 << i)) cur = 0;
			memset(c, 0, (m + 1) << 2);
			if(!cur) continue;
			l = 0;
			calc(r, 0, -1);
			if(l > 1) cur = 0;
			ans += cur;
			
		}
		return ans;
	}
}   user;
