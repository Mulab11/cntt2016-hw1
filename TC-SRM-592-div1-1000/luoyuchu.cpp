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

const double pi = acos(-1.0);

int n;
struct comp
{
	double x, y;
	comp() {x = 0, y = 0;}
	comp(double _a, double _b):x(_a), y(_b) {}
	comp operator + (const comp &b) const
	{
		return comp(x + b.x, y + b.y);
	}
	comp operator - (const comp &b) const
	{
		return comp(x - b.x, y - b.y);
	}
	comp operator * (const comp &b) const
	{
		return comp(x * b.x - y * b.y, x * b.y + y * b.x);
	}
	comp operator * (const double &b) const
	{
		return comp(x * b, y * b);
	}
};

pair<comp, comp> Kf(comp a)//复数开方
{
	pair<comp, comp> ans;
	double tmp = sqrt(a.x * a.x + 4 * a.y * a.y), x2, y2;
	x2 = (a.x + tmp) / 2;
	y2 = (tmp - a.x) / 2;
	if (a.y < 0) {
		return make_pair(comp(sqrt(x2), -sqrt(y2)), comp(-sqrt(x2), sqrt(y2)));
	}
	else {
		return make_pair(comp(sqrt(x2), sqrt(y2)), comp(-sqrt(x2), -sqrt(y2)));
	}
	
}

vector<comp> DFT(vector<int> a)//DFT变化
{
	comp Wn = comp(cos(2 * pi / n), sin(2 * pi / n)), X, Xn;
	vector<comp> s;
	X = comp(1, 0);
	s.resize(n);
	for (int i = 0; i < n; ++i) {
		Xn = comp(1, 0);
		for (int j = 0; j < n; ++j) {
			s[i] = s[i] + (Xn * a[j]);
			Xn = Xn * X;
		}
		X = X * Wn;
	}
	return s;
}

vector<int> IDFT(vector<comp> a)//逆DFT
{
	comp Wn = comp(cos(2 * pi / n), -sin(2 * pi / n)), X, Xn;
	vector<comp> s;
	vector<int> ts;
	X = comp(1, 0);
	s.resize(n);
	for (int i = 0; i < n; ++i) {
		Xn = comp(1, 0);
		for (int j = 0; j < n; ++j) {
			s[i] = s[i] + (Xn * a[j]);
			Xn = Xn * X;
		}
		X = X * Wn;
	}
	for (int i = 0; i < n; ++i) {
		s[i].x /= n;
	}
	ts.resize(n);
	for (int i = 0; i < n; ++i) {
		ts[i] = (int)(s[i].x + 0.5);
	}
	return ts;
}

bool Check(vector<int> a, vector<int> b)//检查合法
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			b[(i + j) % n] -= a[i] * a[j];
		}
	}
	for (int i = 0; i < n; ++i) {
		if (b[i] != 0) {
			return 0;
		}
	}
	return 1;
}

class SplittingFoxes2 {
    public:
    vector<int> getPattern(vector<int> amount) {
		vector<comp> dv, B;
		vector<int> ans, p, wa;
		bool ok = 0;
		n = amount.size();//我们发现最终的amount就是p的一个循化卷积
		dv = DFT(amount);//将amount化为点值表示
		ans.resize(n, (int)2e9);
		int N = (1 << (n / 2 + 1));
		int tmp;
		B.resize(n);//对点值表示进行开方
		for (int i = 0; i < N; ++i) {
			tmp = i;
			for (int j = 0; j <= (n / 2); ++j) {//由于p的对称性，所以点值也是对称的，只需要枚举一半的正负符号
				if (tmp & 1) {
					B[(-j + n) % n] = B[j] = Kf(dv[j]).first;
				}
				else {
					B[(-j + n) % n] = B[j] = Kf(dv[j]).second;
				}
				tmp >>= 1;
			}
			p = IDFT(B);//逆DFT
			if (Check(p, amount) && p < ans) {//检查是否合法并更新答案
				ok = 1;
				ans = p;
			}
		}
		wa.resize(1);
		wa[0] = -1;
		if (!ok) return wa;//无解
        else return ans;//返回答案
    }
};
