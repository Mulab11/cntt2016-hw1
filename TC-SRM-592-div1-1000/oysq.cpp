#line 2 "SplittingFoxes2.cpp"  
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

const int N = 25;
const double pi = acos(-1.0);
const double eps = 1e-4;

int n;

struct cpx {// 复数类的基本运算
	double a, b;// a + bi
	cpx() {}
	cpx(double _a, double _b):a(_a), b(_b) {}
	friend cpx operator + (const cpx &p, const cpx &q) {
		return cpx(p.a + q.a, p.b + q.b);
	}
	friend cpx operator - (const cpx &p, const cpx &q) {
		return cpx(p.a - q.a, p.b - q.b);
	}
	friend cpx operator * (const cpx &p, const cpx &q) {
		return cpx(p.a * q.a - p.b * q.b, p.a * q.b + p.b * q.a);
	}
	friend cpx operator / (const cpx &p, const double &k) {
		return cpx(p.a / k, p.b / k);
	}
};

std::vector<cpx> g, r, h;

std::vector<int> p, cur, ans;

std::vector<cpx> dft(std::vector<cpx> g, int f) {// 长度为n的dft，f = 1表示正向，f = -1表示idft
	std::vector<cpx> h;
	h.resize(n, cpx(0, 0));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			cpx t = cpx(cos(-2 * pi * f * i * j / n), sin(-2 * pi * f * i * j / n));
			h[i] = h[i] + g[j] * t;
		}
	}
	if(f == -1) {
		for(int i = 0; i < n; ++i)
			h[i] = h[i] / n;
	}
	return h;
}

int sgn(double x) {// x的正负
	if(x < -eps) return -1;
	else return x > eps;
}

bool isint(double x) {// 判断x是否是整数
	return ceil(x) - x < eps || x - floor(x) < eps;
}

int getint(double x) {// 将x变成整数
	if(ceil(x) - x < eps) return ceil(x);
	else return floor(x);
}

bool dfs(int x) {
	if(x > n / 2) {
		h = dft(r, -1);
		for(int i = 0; i < n; ++i) {
			if(sgn(h[i].b)) return false;
			if(sgn(h[i].a) == -1) return false;
			if(i && fabs(h[i].a - h[n - i].a) > eps) return false;
			if(!isint(h[i].a)) return false;
			cur[i] = getint(h[i].a);
		}
		for(int i = 0; i < n; ++i) {
			int x = 0;
			for(int j = 0; j < n; ++j)
				x += cur[j] * cur[(i - j + n) % n];
			if(x != p[i]) return false;
		}
		if(!SZ(ans) || cur < ans) ans = cur;
		return true;
	}
	// 设当前g[x] = a + bi，那么要求的r[x] = sqrt(g[x])
	// (c + di) ^ 2 = a + bi我们可以求出c ^ 2 = (a + sqrt(a ^ 2 + b ^ 2)) / 2, d ^ 2 = c ^ 2 - a
	// 枚举c和d的正负性，因为g和r都是对称的，因此只要枚举n / 2个就行了，复杂度O(2 ^ {n / 2} * n ^ 2)
	double a = g[x].a, b = g[x].b;
	double c2 = (a + sqrt(a * a + b * b)) / 2, d2 = c2 - a;
	if(c2 >= -eps && d2 >= -eps) {
		double c = sqrt(std::max(c2, 0.0)), d = sqrt(std::max(d2, 0.0));
		double p[2] = {-1, 1};
		bool flag = false;
		for(int i = 0; i < 2 - (sgn(c) == 0); ++i)// 枚举c的正负性
			for(int j = 0; j < 2 - (sgn(d) == 0); ++j)// 枚举d的正负性
				if(sgn(p[i] * c * p[j] * d) == sgn(b)) {// 因为2cd = b，因此cd和b的正负性是一样的，这样就限制了每位最多两种不同方案
					r[x] = cpx(p[i] * c, p[j] * d);
					if(x) r[n - x] = r[x];// 对称的
					if(dfs(x + 1)) flag = true;
				}
		return flag;
	}
	else return false;
}

class SplittingFoxes2 {  
public:  
	vector <int> getPattern(vector <int> _p) {
		// 因为给出的p相当于是原序列对自己在长度为n下的循环卷积
		// 我们的任务就是给它开方
		p = _p;
		n = SZ(p);
		g.clear();
		for(auto i : p) g.pb(cpx(i, 0));
		g = dft(g, 1);// 点值表示
		r.resize(n, cpx(0, 0));
		cur.resize(n, 0);
		ans.clear();
		if(!dfs(0)) return {-1};// 无解
		return ans;
	}  
};  
