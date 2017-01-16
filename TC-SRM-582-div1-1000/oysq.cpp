#line 2 "SemiPerfectPower.cpp"  
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

const int LIM = 440000;

int p[LIM + 9], pn;
int mu[LIM + 9];
int minp[LIM + 9];
bool is[LIM + 9];

void euler(int n) {// 欧拉筛法
	mu[1] = 1, pn = 0;
	for(int i = 2; i <= n; ++i) {
		if(!is[i]) p[++pn] = i, mu[i] = -1, minp[i] = i;
		for(int j = 1; j <= pn && p[j] * i <= n; ++j) {
			int nex = p[j] * i;
			is[nex] = true;
			minp[nex] = p[j];
			if(i % p[j] == 0) break;
			mu[nex] = -mu[i];
		}
	}
}

ll r2(ll n) {// n ^ (1 / 2)
	ll l = 0, r = 1e9;
	while(l < r) {
		ll mid = (l + r + 1) >> 1;
		if(mid * mid > n) r = mid - 1;
		else l = mid;
	}
	return l;
}

ll solve2(ll n) {// a * b ^ 2
	ll lim = 1;
	while(lim * lim * lim < n) ++lim;
	ll ret = 0;
	for(int a = 1; a <= lim; ++a)// 枚举a
		if(mu[a]) ret += std::max(r2(n / a) - a, 0ll);// 为了避免重复，a不能包含平方因子
	return ret;
}

const int LIM2 = 17000;
const int SZ = 4600000;

int cnt[SZ + 9];
int pos[LIM2 + 9], tot;

ll r3(ll n) {// n ^ (1 / 3)
	ll l = 0, r = 1e6;
	while(l < r) {
		ll mid = (l + r + 1) >> 1;
		if(mid * mid * mid > n) r = mid - 1;
		else l = mid;
	}
	return l;
}

bool check3(int a) {// 检查a是否包含立方因子
	while(a > 1) {
		int x = minp[a], c = 0;
		while(a % x == 0) a /= x, c++;
		if(c > 2) return false;
	}
	return true;
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

ll getcnt(int d, int n) {// sigma{|mu[i * d]|, i <= n}，可以预处理
	if(!n) return 0;
	return cnt[pos[d] + n - 1];
}

ll sum(int n, int k) {// sigma{|mu[i * k]|, i <= n}, n太大，要反演一下缩小范围
	if(!mu[k]) return 0;
	ll ret = 0;
	for(int d = 1; d * d <= k; ++d)
		if(k % d == 0) {
			ret += mu[d] * getcnt(d, n / d);
			if(d * d != k) ret += mu[k / d] * getcnt(k / d, n / (k / d));
		}
	return ret;
}

ll solve3(ll n) {// a * b ^ 3 且不能被表示成 a * b ^ 2
	ll lim = 1;
	while(lim * lim * lim * lim < n) lim++;
	ll lim2 = 1;
	while(lim2 * lim2 * lim2 < n) lim2++;
	tot = 0;
	for(int d = 1; d <= lim; ++d) {// 预处理sigma{|mu[i * d]|, i * d <= lim2}
		pos[d] = tot + 1;
		for(int i = 1; i * d <= lim2; ++i) {
			++tot;
			cnt[tot] = abs(mu[i * d]);
			if(tot > pos[d]) cnt[tot] += cnt[tot - 1];
		}
	}
	ll ret = 0;
	for(int a = 1; a <= lim; ++a)// 枚举a
		if(check3(a))
			for(int k = 1; k * k * k <= a; ++k) {// 计算k ^ 2为ab的最大平方因子的方案数，k <= a ^ (1 / 3)
				int d = gcd(k * k, a), u = k * k / d, v = a / d;
				int ub = r3(n / a) / u, lb = a / u;
				if(ub < lb) continue;
				ret += sum(ub, v) - sum(lb, v);
			}
	return ret;
}

ll calc(ll n) {
	return solve2(n) + solve3(n);
}

class SemiPerfectPower {  
public:  
	long long count(long long L, long long R) {
		euler(LIM);// 欧拉筛法搞出mu[i], minp[i]分别表示莫比乌斯函数，最小质因子
		return calc(R) - calc(L - 1);
	}  
};  
