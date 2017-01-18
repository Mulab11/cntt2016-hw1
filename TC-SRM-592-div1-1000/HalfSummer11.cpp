#line 2 "SplittingFoxes2.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
#define pi M_PI
typedef long long ll;
using namespace std;
struct cpx {
	double r, i;
	cpx() {}
	cpx(double _r, double _i) {r = _r; i = _i;}
	cpx operator + (const cpx &b) { return cpx(r + b.r, i + b.i);}
	cpx operator - (const cpx &b) { return cpx(r - b.r, i - b.i);}
	cpx operator * (const cpx &b) { return cpx(r * b.r - i * b.i, r * b.i + i * b.r);}
}a[maxn], b[maxn], c[maxn], d[maxn];
int n, e[maxn], f[maxn];
void dft(cpx *a, cpx *b, int on) {
	for (int i = 0; i < n; ++i) {
		b[i] = cpx(0, 0);
		for (int j = 0; j < n; ++j)
			b[i] = b[i] + a[j] * cpx(cos(2 * pi * i * j * on / n), sin(2 * pi * i * j * on / n));
	}
	if (on == -1)
		for (int i = 0; i < n; ++i) b[i].r /= n;
}
cpx Sqrt(cpx a) {
	double theta = atan2(a.i, a.r), l = sqrt(a.i * a.i + a.r * a.r);
	l = sqrt(l); theta /= 2.0;
	return cpx(l * cos(theta), l * sin(theta));
}
class SplittingFoxes2 {
	public:
		vector <int> getPattern(vector <int> ac) {
			n = ac.size();
			for (int i = 0; i < n; ++i) 
				a[i] = cpx(ac[i] * 1.0, 0);
			dft(a, b, 1);
			for (int i = 0; i < n; ++i) b[i] = Sqrt(b[i]);
			vector <int> ans;
			int m = n / 2 + 1;
			for (int s = 0; s < (1 << m); ++s) {
				for (int i = 0; i < n; ++i) c[i] = b[i];
				for (int i = 0; i < n; ++i) {
					if (i < m) {
						if (s & (1 << i)) c[i] = cpx(0, 0) - c[i];
					} else {
						c[i] = c[n - i];
					}
				}
				dft(c, d, -1);
				for (int i = 0; i < n; ++i) e[i] = int(d[i].r + 0.5);
				for (int i = 0; i < n; ++i) f[i] = 0;
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < n; ++j)
						f[(i + j) % n] += e[i] * e[j];
				bool flag = 1;
				for (int i = 0; i < n; ++i)
					if (f[i] != ac[i]) flag = 0;
				for (int i = 1; i < n; ++i)
					if (e[i] != e[n - i]) flag = 0;
				if (flag) {
					vector <int> tmp;
					for (int i = 0; i < n; ++i) tmp.pb(e[i]);
					if (!ans.size() || tmp < ans) 
						ans = tmp;
				}
			}
			if (!ans.size()) ans.pb(-1);
			return ans;
		}
};
