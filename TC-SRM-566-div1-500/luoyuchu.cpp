#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 375;
const int mod = 1e9+7;

int n;
LL Day;

vector<int> Mult(vector<int> a, vector<int> b)//移动方案乘法原理合并
{
	int sz = a.size();
	vector<int> c;
	c.clear();
	c.resize(sz);
	for (int i = 0; i < sz; ++i) {
		for (int j = 0; j < sz; ++j) {
			c[i] = (c[i] + (LL)a[j] * b[abs(i - j)] % mod) % mod;
		}
	}
	return c;
}

vector<int> Dotour(LL tour)//计算整周期的移动方案
{
	vector<int> f, g, s;//f[i], g[i], s[i]均表示从0出发经过现有天数到达i的方案数
	f.clear();
	f.resize(n);
	f[0] = 1;
	for (int i = 1; i <= n; ++i) {//暴力求出一个周期的从0出发到各个点的方案数
		g.clear();
		g.resize(n);
		for (int j = 0; j < n; ++j) {
			(g[(j + i) % n] += f[j]) %= mod;
			if ((j + i) % n != (j - i + n) % n) (g[(j - i + n) % n] += f[j]) %= mod;
		}
		f = g;
	}
	s.clear();
	s.resize(n);
	s[0] = 1;
	while (tour) {//做周期快速幂
		if (tour & 1) {
			s = Mult(s, f);//移动方案乘法原理合并
		}
		f = Mult(f, f);
		tour >>= 1;
	}
	return s;
}

int Solve()
{
	vector<int> f, g;
	LL tour = Day / n;//对于没n天为一个移动周期
	Day %= n;//整周期之外的暴力算
	f = Dotour(tour);
	for (int i = 1; i <= Day; ++i) {//对于剩余不足一周期的天数暴力Dp
		g.clear();
		g.resize(n);
		for (int j = 0; j < n; ++j) {
			(g[(j + i) % n] += f[j]) %= mod;
			if ((j + i) % n != (j - i + n) % n) (g[(j - i + n) % n] += f[j]) %= mod;
		}
		f = g;
	}
	return f[0];
}

class PenguinEmperor {
    public:
    int countJourneys(int numCities, long long daysPassed) {
		n = numCities;
		Day = daysPassed;
        return Solve();
    }
};

