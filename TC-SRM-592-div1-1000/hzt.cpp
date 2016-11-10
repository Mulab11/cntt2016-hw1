#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#define Rep(i, x, y) for (int i = x; i <= y; i ++)
#define Dwn(i, x, y) for (int i = x; i >= y; i --)
#define RepE(i, x) for (int i = pos[x]; i; i = g[i].nex)
using namespace std;
typedef long long ll;
typedef double db;
const int N = 28;
int n;
db PI = M_PI;
struct comp {
	db r, i;
	comp() {}
	comp(db r0, db i0) { r = r0, i = i0; }
} w[N];
comp operator* (comp a, comp b) {
	return comp(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}
comp operator+ (comp a, comp b) {
	return comp(a.r + b.r, a.i + b.i);
}
comp sqrt(comp z){
	db arg = atan2(z.i, z.r);
	arg /= 2.0;
	db l = sqrt(z.r * z.r + z.i * z.i);
	l = sqrt(l);
	comp res = {l * cos(arg), l * sin(arg)};
	return res;
}
vector<comp> dft(vector<comp> a) {
	vector<comp> res;
	Rep(i, 0, n - 1) {
		comp sum(0, 0);
		Rep(j, 0, n - 1) sum = sum + a[j] * w[i * j % n];
		res.push_back(sum);
	}
	return res;
}
class SplittingFoxes2{
public:
	bool check(vector<int> v, vector<int> a) {
		Rep(i, 0, n - 1) {
			if (v[i] < 0) return 0;
			int s = 0;
			Rep(j, 0, n - 1) s += v[j] * v[(i - j + n) % n];
			if (s != a[i]) return 0;
		}
		return 1;
	}
	bool cmp(vector<int> v, vector<int> a) {
		Rep(i, 0, n - 1) {
			if (v[i] < a[i]) return 1;
			else if (v[i] > a[i]) return 0;
		}
		return 0;
	}
	vector<int> getPattern(vector<int> a) {
		n = a.size();
		vector<int> ans;
		w[0] = comp(1, 0);
		Rep(i, 1, n - 1) w[i] = w[i - 1] * comp(cos(2 * PI / n), sin(2 * PI / n));
		vector<comp> b;
		Rep(i, 0, n - 1) b.push_back(comp(a[i], 0));
		b = dft(b);
		Rep(i, 0, n - 1) b[i] = sqrt(b[i]);
		Rep(i, 0, n - 1) w[i].i = -w[i].i;
		int m = n / 2 + 1;
		Rep(k, 0, (1 << m) - 1) {
			vector<comp> d;
			Rep(j, 0, n - 1) d.push_back(b[j]);
			Rep(j, 0, n - 1) {
				if (k & (1 << min(j, n - j))) d[j].r = -d[j].r, d[j].i = -d[j].i;
			}
			d = dft(d);
			vector<int> v;
			Rep(j, 0, n - 1) {
				v.push_back( int(d[j].r / n + 0.45865856387657545) ); //
			}
			if (check(v, a) && (ans.empty() || cmp(v, ans))) ans = v;
		}
		if (ans.empty()) ans.push_back(-1);
		return ans;
	}
};