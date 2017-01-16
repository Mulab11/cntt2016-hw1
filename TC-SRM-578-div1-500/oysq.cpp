#line 2 "WolfInZooDivOne.cpp"  
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

const int N = 300;
const int MOD = 1000000007;

std::vector<int> l, r;
int p[N + 9];
int f[N + 9][N + 9];// f[i][j] 表示最后一个1在i，倒数第二个在j的方案数
int g[N + 9][N + 9];// g[i][j] = sigma{f[i][k], 0 <= k <= j}

std::vector<int> get(std::vector<std::string> str) {
	std::string s;
	for(int i = 0; i < SZ(str); ++i) s += str[i];
	s += ' ';
	std::vector<int> ret;
	for(int i = 0; i < SZ(s); ++i) {
		int j = i, num = s[i] - '0';
		while(s[j + 1] != ' ') ++j, num = num * 10 + s[j] - '0';
		ret.pb(num);
		i = j + 1;
	}
	return ret;
}

class WolfInZooDivOne {  
public:  
	int count(int n, vector <string> sl, vector <string> sr) {  
		l = get(sl), r = get(sr);
		for(int i = 0; i < n; ++i) p[i] = i;
		for(int i = 0; i < SZ(l); ++i)
			for(int j = l[i]; j <= r[i]; ++j)
				chkmin(p[j], l[i]);// p[i] 表示包含i的限制中左边界的最小值
		int ans = 1 + n;//空集和只选一个的方案
		for(int i = 1; i < n; ++i) {
			int ml = p[i];// j 前面的那个1的位置 < ml
			for(int j = i - 1; j >= 0; --j) {
				f[i][j] = 1, chkmin(ml, j);
				if(ml) (f[i][j] += g[j][ml - 1]) %= MOD;
				g[i][j] = f[i][j];
			}
			for(int j = 1; j < i; ++j)
				(g[i][j] += g[i][j - 1]) %= MOD;// 更新前缀和
		}
		for(int i = 1; i < n; ++i)// 统计答案
			(ans += g[i][i - 1]) %= MOD;
		return ans;
	}  
};  
