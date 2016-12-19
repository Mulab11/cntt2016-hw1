#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class XorAndSum
{
	ll G[64]; // 线性基
public:
	ll maxSum(vector<ll> val)
	{
		memset(G, 0, sizeof G);
		int zero_count = 0;
		// 高斯消元求出每个线性基，这一步完全符合题目要求
		for(int _ = 0; _ != (int) val.size(); ++_)
		{
			for(ll x = val[_]; x; )
			{
				int k = 63 - __builtin_clzll(x);
				if(!G[k]) {G[k] = x; goto next_step;}
				x ^= G[k];
			}
			++zero_count;
			next_step: continue;
		}
		// 保证有基的位置只有这个基才为 1
		ll max = 0;
		for(int i = 0; i != 64; ++i) if(G[i])
		{
			for(int j = i + 1; j != 64; ++j) if(G[j] & (1ll << i)) G[j] ^= G[i];
			max ^= G[i];
		}
		// 贪心策略：
		// 1. 把最高位的基异或上其他所有的，构造成最大异或和
		// 2. 把其它的基和所有的 0 异或上最大异或和
		// 正确性：除了等于最大异或和之外的其他元素，减少的量都是尽可能小的
		ll ans = 0;
		for(int i = 64; i--; ) if(G[i]) ans += (ans ? (max ^ G[i]) : max);
		return ans + max * zero_count;
	}
}	user;