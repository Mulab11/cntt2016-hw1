#line 2 "CharacterBoard.cpp"  
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

const int MOD = 1000000009;

int fpm(int a, int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ll)ret * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return ret;
}

int calc(int l, const std::vector<std::string> &g, int W, int i0, int j0) {// 对于给定的S的长度l，求出不同串的个数
	std::unordered_map<int, int> p;// 用hash来保存出现的位置的值
	int n = SZ(g), m = SZ(g[0]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			int pos = ((ll)(i + i0) * W + (j + j0)) % l;
			if(!p.count(pos)) p[pos] = g[i][j] - 'a';
			else if(p[pos] != g[i][j] - 'a') return 0;// 有冲突则无解
		}
	return fpm(26, l - SZ(p));// 否则方案数为26 ^ 没有限制的位置数
}

class CharacterBoard {  
public:  
	int countGenerators(vector <string> g, int W, int i0, int j0) {  
		int n = SZ(g), m = SZ(g[0]), ret = 0;
		std::unordered_set<int> s;
		for(int l = 1; l <= W && l < n * m; ++l)// 小范围暴力
			(ret += calc(l, g, W, i0, j0)) %= MOD, s.insert(l);
		if(W >= n * m) {
			// 先假设所有的g中的串都不相交
			(ret += (ll)(fpm(26, W - n * m + 1) - 1 + MOD) * fpm(25, MOD - 2) % MOD) %= MOD;// 26 ^ 0 + 26 ^ 1 + ... + 26 ^ {W - n * m}
			// 然后枚举如果g中的串相交，可能的S串的长度
			for(int i = 1; i < n; ++i)// 枚举相隔的行数
				for(int j = -m + 1; j < m; ++j) {// 枚举相交位置
					ll w = (ll)i * W - j;// 长度 | w
					for(int k = 1; (ll)k * k <= w && k <= W; ++k)// 约数个数很少，可以直接暴力
						if(w % k == 0) {
							if(!s.count(k)) s.insert(k), (ret += calc(k, g, W, i0, j0)) %= MOD, (ret += MOD - fpm(26, k - n * m)) %= MOD;
							if(w / k <= W && !s.count(w / k)) s.insert(w / k), (ret += calc(w / k, g, W, i0, j0)) %= MOD, (ret += MOD - fpm(26, w / k - n * m)) %= MOD;
						}
				}
		}
		return ret;
	}  
};  
