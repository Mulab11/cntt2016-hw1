#line 2 "WolfPack.cpp"  
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
const int LIM = 200000;

int n;
std::vector<int> nx, ny;

int fac[LIM + 9];
int inv[LIM + 9];
int C[LIM + 9];

int fpm(int a, int b) {// 快速幂
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ll)ret * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return ret;
}

int solve(std::vector<int> p, int m) {// 对于一维坐标点集p，m次操作，求出方案
	// 预处理n!, 1/n!, C(m, i)
	fac[0] = 1;
	for(int i = 1; i <= m; ++i) fac[i] = (ll)fac[i - 1] * i % MOD;
	inv[m] = fpm(fac[m], MOD - 2);
	for(int i = m - 1; i >= 0; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % MOD;
	for(int i = 0; i <= m; ++i) C[i] = (ll)fac[m] * inv[i] % MOD * inv[m - i] % MOD;
	
	int ret = 0;
	for(int i = -LIM; i <= LIM; ++i) {// 枚举最后在一起的位置
		int cur = 1;
		for(int j = 0; j < n; ++j) {
			int d = abs(i - p[j]);
			if((d & 1) != (m & 1) || d > m) {// 不合法情况
				cur = 0;
				break;
			}
			cur = (ll)cur * C[(m - d) >> 1] % MOD;
			// 设一种方向的操作数为a, 另一种为m - a, 不妨设a < m / 2, 那么因为(m - a) - a = d, a = (m - d) / 2
			// 所以此时的方案数为C(m, (m - d) / 2)
		}
		(ret += cur) %= MOD;
	}
	return ret;
}

class WolfPack {  
public:  
	int calc(vector <int> x, vector <int> y, int m) {  
		n = SZ(x), nx.clear(), ny.clear();
		for(int i = 0; i < n; ++i) nx.pb(x[i] - y[i]), ny.pb(y[i] + x[i]);// 旋转45°之后两维独立
		return (ll)solve(nx, m) * solve(ny, m) % MOD;// 分开考虑x, y再乘起来
	}  
};  
