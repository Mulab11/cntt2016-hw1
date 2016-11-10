#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

int N;
ll G[64], M, ans;

void dfs(int i, ll v)
{
	if(!i--) return (void) (ans += v <= M);
	if(!G[i]) return dfs(i, v);
	// 如果 v 异或到后面的最大异或子集都不如 M 大，则直接计算答案
	// 如果 v 异或到后面的最小异或子集都比 M 大，则返回
	ll max = v, min = v;
	int c = 0;
	for(int j = i; j >= 0; --j) if(G[j])
	{
		++c;
		if(~max & 1ll << j) max ^= G[j];
		if( min & 1ll << j) min ^= G[j];
	}
	if(max <= M) return (void) (ans += (1ll << c));
	if(min >  M) return;
	dfs(i, v);
	dfs(i, v ^ G[i]);
}

class XorCards
{
public:
	ll numberOfWays(vector<ll> arr, ll lim)
	{
		// 高斯消元
		N = arr.size();
		int T = N;
		for(int i = 0; i != N; ++i)
		{
			ll x = arr[i];
			for(int k; x; )
			{
				k = 63 - __builtin_clzll(x);
				if(!G[k]) {G[k] = x; --T; break;}
				x ^= G[k];
			}
		}
		// 爆搜
		M = lim;
		dfs(64, 0);
		return ans << T;
	}
}	user;
