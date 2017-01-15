#line 2 "DefectiveAddition.cpp"  
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

const int MOD = 1000000007;

class DefectiveAddition {  
public:  
	int count(vector <int> cards, int n) {  
		std::sort(cards.begin(), cards.end());// 升序排序
		if(cards.back() == 0) return n == 0;// 特判全为0的序列
		int bn = 0, bc = 0;
		while((1 << bn) <= n) bn++;
		while((1 << bc) <= cards.back()) bc++;
		bn--, bc--;// 找到cards.back()和n的最大的二进制位，分别记为bc, bn
		if(bn > bc) return 0;// 如果cards.back()的最大二进制位 < n的最大二进制位，那么cards不可能构成n
		int f[2] = {1, 0}, g[2] = {0};// f[x] 表示cards除了cards.back()之外，二进制上bc位为x的方案数
		for(int i = 0; i < SZ(cards) - 1; ++i) {
			g[0] = ((ll)f[0] * std::min(cards[i] + 1, 1 << bc) + (ll)f[1] * std::max(cards[i] - (1 << bc) + 1, 0)) % MOD;
			g[1] = ((ll)f[1] * std::min(cards[i] + 1, 1 << bc) + (ll)f[0] * std::max(cards[i] - (1 << bc) + 1, 0)) % MOD;
			f[0] = g[0], f[1] = g[1];
		}
		int ret = f[n >> bc & 1];// 如果除去cards.back()之外构成的bc位和n的bc位相同，那么cards.back()这一位为0，此时cards.back() 的 0 ~ bc - 1位可以任意0/1，因此无论前面0 ~ bc - 1位怎么取都能变成n
		if(bc >= 0) {// 如果不同，那么cards.back()这一位为1，递归进去算，终止条件就是所有数都变成了0
			cards[SZ(cards) - 1] -= 1 << bc;
			n ^= 1 << bc;
			(ret += count(cards, n)) %= MOD;
		}
		return ret;
	}    
};
