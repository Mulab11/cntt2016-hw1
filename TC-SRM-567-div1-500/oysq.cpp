#line 2 "StringGame.cpp"  
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

const int N = 50, SIGMA = 26;

int cnt[N + 9][SIGMA];// cnt[i][j] 表示第i个字符串字符j出现的次数

class StringGame {  
public:  
	vector <int> getWinningStrings(vector <string> S) {
		memset(cnt, 0, sizeof cnt);
		std::vector<int> ret;
		int n = SZ(S);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < SZ(S[i]); ++j)
				cnt[i][S[i][j] - 'a']++;// 计算cnt
		for(int i = 0; i < n; ++i) {
			ll eq[SIGMA] = {0}, g[SIGMA] = {0};// eq[c] 表示cnt[j][c] == cnt[i][c]的j的集合, g[c]表示 cnt[j][c] > cnt[i][c]的j的集合
			for(int j = 0; j < n; ++j)
				if(i != j) 
					for(int k = 0; k < SIGMA; ++k)
						if(cnt[i][k] == cnt[j][k])
							eq[k] |= 1ll << j;
						else if(cnt[i][k] < cnt[j][k])
							g[k] |= 1ll << j;
			ll s = (1ll << n) - 1 - (1ll << i);
			while(true) {
				ll t = s;
				for(int j = 0; j < SIGMA; ++j)
					if(!g[j])
						s &= eq[j];// 对于g[j] = 0，也就是没有其他字符串有更多的j的情况下，我们可以把集合与上eq[j]得到有可能小于当前字符串的集合
				if(t == s) break;
				for(int j = 0; j < SIGMA; ++j)
					g[j] &= s;// 将g[j]缩小到只包含可能小于当前字符串的集合的元素
			}
			if(!s) ret.pb(i);// 当可能小于的集合为空时，先手有必胜方案
		}
		return ret;
	}    
};  
