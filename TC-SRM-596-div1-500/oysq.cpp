#include <bits/stdc++.h>

#define ll long long
#define uint unsigned

#define debug(...) fprintf(stderr, __VA_ARGS__)

#define SZ(x) ((int)(x).size())
#define pb push_back

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(y < x) x = y;}

template<class T>
inline void read(T &x) {
	char c;int f = 1;x = 0;
	while(((c = getchar()) < '0' || c > '9') && c != '-');
	if(c == '-') f = -1;else x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
	x *= f;
}

class BitwiseAnd {
public:
	std::vector<ll> lexSmallest(std::vector<ll> sub, int n) {
		// 判断给定的subset满不满足条件1
		for(int i = 0; i < SZ(sub); ++i)
			for(int j = 0; j < i; ++j)
				if(!(sub[i] & sub[j]))
					return {};
		int c[60] = {0};
		n -= SZ(sub);
		for(auto i : sub)
			for(ll j = i; j; j -= j & -j)
				c[__builtin_ctzll(j & -j)]++;
		// 判断给定的subset满不满足条件2
		for(int i = 0; i < 60; ++i)
			if(c[i] > 2) return {};
		std::vector<ll> ans = sub;
		while(n--) {
			// 每次贪心加入最小的数
			ll v = 0;
			for(int j = 59; j >= 0; --j)
				if(c[j] == 1) {// 先让加入的值能和之前的每个数有至少一个公共bit
					ll t = v;
					// 判断如果这一位为0是否有解
					for(int k = 0; k < j; ++k)
						if(c[k] < 2) t |= 1ll << k;
					bool ok = true;
					for(auto x : ans)
						if(!(t & x)) {
							ok = false;
							break;
						}
					// 如果没解，那么这一位必须为1
					if(!ok) v |= 1ll << j, c[j]++;
				}
			// 检查是否和之前的数 & = 1
			for(auto x : ans)
				if(!(v & x))
					return {};
			// 为了和之后的值 & = 1先预留一些位置
			int r = n;
			for(int j = 0; j < 60; ++j)
				if(!c[j] && r) {
					r--;
					c[j]++;
					v |= 1ll << j;
				}
			// 判断位置是否足够
			if(r) return {};
			ans.pb(v);
		}
		std::sort(ans.begin(), ans.end());
		return ans;
	}
};
