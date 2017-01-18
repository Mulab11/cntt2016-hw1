#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
#include <complex>
using namespace std;
typedef complex<double> Complex;
const double PI = acos(-1.0);
const int MAXN = 30;
void dft(Complex *x, int n, int mul)
{
	static Complex y[MAXN], w[MAXN];
	for(int i = 0; i < n; i++)
		w[i] = Complex(cos(i * 2 * PI / n), mul * sin(i * 2 * PI / n));
	for(int i = 0; i < n; i++)
	{
		y[i] = 0;
		for(int j = 0; j < n; j++)
			y[i] += x[j] * w[i * j % n];
	}
	for(int i = 0; i < n; i++)
		x[i] = y[i];
	if(mul == -1)
		for(int i = 0; i < n; i++)
			x[i] /= n;
}
vector<int> sqr(const vector<int> now)
{
	vector<int> ret(now.size(), 0);
	for(int i = 0; i < now.size(); i++)
		for(int j = 0; j < now.size(); j++)
			ret[(i + j) % now.size()] += now[i] * now[j];
	return ret;
}
class SplittingFoxes2
{
private:
	int n;//N
	vector<int> amount;
	Complex a[MAXN];//amount
	Complex b[MAXN];//pattern
	vector<int> ans;
	void test(int S)
	{
		for(int i = 0; i < n; i++)
			if(((S >> i) & 1) || ((S >> (n - i)) & 1))
				b[i] = -a[i];
			else
				b[i] = a[i];
		dft(b, n, -1);
		vector<int> now(n, 0);
		for(int i = 0; i < n; i++)
		{
			now[i] = round(b[i].real());
			if(now[i] < 0 || (i > n - i && now[i] != now[n - i]) || fabs(now[i] - b[i].real()) > 0.01)//invalid pattern; reduce some calculations if it's not an integer
				return;
		}
		if(sqr(now) == amount && now < ans)
			ans = now;
	}
public:
	vector<int> getPattern(vector<int> amount)
	{
		this->amount = amount;
		n = amount.size();
		for(int i = 0; i < n; i++)
			a[i] = amount[i];
		dft(a, n, 1);
		//for(int i = 0; i < n; i++)
		//	printf("%d: (%lf,%lf)\n", i, a[i].real(), a[i].imag());
		for(int i = 0; i < n; i++)
			a[i] = sqrt(a[i]);
		ans.assign(1, 1010101010);//inf
		for(int i = 0; i < (1 << ((n / 2) + 1)); i++)//try every +/- of sqrt
			test(i);
		if(ans[0] == 1010101010)
			ans[0] = -1;
		return ans;
	}
};

