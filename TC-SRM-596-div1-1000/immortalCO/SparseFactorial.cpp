#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int f[1000010], s[1000010];
vector<int> q[1000010];

template<class T> void reinit(T& t) {t.~T(); new (&t)T;}

class SparseFactorial
{
public:
	ll getCount(ll l, ll r, ll inp)
	{
		int mod = inp;
		// 考虑对 mod 进行因数分解
		// p1^c1 * p2^c2 * ...
		// 那么我们考虑什么样的数字是可以做的
		// 考虑在模意义下的数 x，它可能由一个模意义下距离为 d 的平方数贡献一个因数
		// 我们分质因数考虑
		int M = 0;
		for(; (ll) M * M <= r; ++M) s[M] = (ll) M * M % mod;
		// 考虑对于每个 i 处理 f[i] 表示如果 x%mod==i 且 x>f[i]*f[i] 就合法
		// 每个质因数分别考虑
		for(int P = 2, T = mod; T != 1; ++P) if(T % P == 0)
		{
			int C = 0;
			while(T % P == 0) T /= P, ++C;
			for(int j = 0; j != P; ++j) reinit(q[j]);
			for(int i = 0; i != M; ++i)
			{
				int p = s[i] % P;
				if(q[p].size() < C) q[p].push_back(i);
			}
			// 开始更新 f
			for(int i = 1; i != mod; ++i) if(f[i] != 1000000000)
			{
				int rem = i % P, left = C, p = 0;
				// 每一个都至少会贡献 1，因此暴力即可！！！！！
				while(p != (int) q[rem].size() && left)
				{
					int cur = (s[q[rem][p++]] - i + mod) % mod;
					while(left && cur % P == 0) cur /= P, --left;
				}
				if(!left) f[i] = max(f[i], q[rem][p - 1]);
				else f[i] = 1000000000;
			}
		}
		ll ans = 0;
		for(int i = 0; i != mod; ++i) if(f[i] != 1000000000)
		{
			ans += (r - i + mod) / mod - (max(l - 1, (ll) f[i] * f[i]) - i + mod) / mod;
		}
		return ans;
	}
}	user;
