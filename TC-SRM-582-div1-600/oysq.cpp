#line 2 "ColorfulBuilding.cpp"  
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

const int N = 1300;
const int MOD = 1000000009;

int n;
int fac[N + 9], inv[N + 9];
int f[N + 9][N + 9];

std::map<pii, int> id;

int each[N + 9];

std::vector<int> get(const std::vector<std::string> &a, const std::vector<std::string> &b) {
	std::string u, v;
	for(auto i : a) u += i;
	for(auto i : b) v += i;
	std::vector<int> p;
	int cnt = 0;
	for(int i = 0; i < SZ(u); ++i) {
		pii cur = mp(u[i], v[i]);
		if(!id.count(cur)) id[cur] = cnt++;
		p.pb(id[cur]);
	}
	return p;
}

int fpm(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = (ll)r * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return r;
}

class ColorfulBuilding {
public:
	int count(vector <string> color1, vector <string> color2, int L) {
		id.clear();
		std::vector<int> col = get(color1, color2);
		n = SZ(col);
		// 预处理阶乘 & 阶乘逆元
		fac[0] = 1;
		for(int i = 1; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % MOD;
		inv[n] = fpm(fac[n], MOD - 2);
		for(int i = n - 1; i >= 0; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % MOD;
		// dp : f[i][j] 表示当前选j，在j ~ n中已经有i段的方案数
		f[1][n] = 1;
		for(int l = 1; l <= L + 1; ++l) {
			std::fill(each, each + SZ(id), 0);
			for(int i = n - 1, pre = 0; i >= 0; --i) {
				// f[l - 1][j] 转移到 f[l][i] 的方案数相当于将j - i - 1个数插到n - j个数内的方案数 = (n - i - 1)! / (n - j)!
				int &v = f[l][i];
				(pre += (ll)f[l - 1][i + 1] * inv[n - i - 1] % MOD) %= MOD;
				(each[col[i]] += ((ll)f[l][i + 1] * inv[n - i - 1] % MOD + MOD - (ll)f[l - 1][i + 1] * inv[n - i - 1] % MOD) % MOD) %= MOD;
				v = (pre + (i ? each[col[i - 1]] : 0)) % MOD;
				v = (ll)v * fac[n - i - 1] % MOD;
			}
		}
		return f[L + 1][0];
	}  
};  
