#line 2 "XorCards.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int B = 50;

ll bit[B];
int s[B];

class XorCards {  
public:  
	ll numberOfWays(vector<ll> v, ll k) {  
		ll ex = 1;
		memset(bit, 0, sizeof bit);
		// 求出线性基
		for(auto a : v) {
			bool fl = false;
			for(int i = B - 1; i >= 0; --i)
				if(a >> i & 1) {
					if(bit[i]) a ^= bit[i];
					else {
						bit[i] = a;
						fl = true;
						break;
					}
				}
			if(!fl) ex <<= 1;// 额外的数可以随便加上或者不加上
		}
		// 前缀和
		for(int i = 0; i < B; ++i)
			s[i] = (bit[i] > 0) + (i ? s[i - 1] : 0);
		ll ret = 0, cur = 0;
		for(int i = B - 1; i >= 0; --i)
			if(k >> i & 1) {
				if(bit[i]) {
					ret += 1ll << (s[i] - 1);// 这一位可以变成0，后面的随便选
					if(!(cur >> i & 1)) cur ^= bit[i];// 让cur >= k
				}
				else {
					if(!(cur >> i & 1)) {// cur一定 < k，后面的随便选
						ret += 1ll << s[i];
						break;
					}
				}
			}
			else {
				if(cur >> i & 1) {
					if(bit[i]) cur ^= bit[i];// 可以把这一位变成0
					else break;// 不能变成0，那么cur一定 > k
				}
			}
		if(cur == k) ret++;// 之前统计的是 < k的答案
		return ret * ex;
	}    
};  
