#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#include <complex>
typedef complex<long double> Comp;
const int inf = 1e9;
const long double eps = 1e-6;
const long double pi = acosl(-1);
int n;
Comp w[25];
vector<int> ans;

vector<Comp> convert(vector<int> v)
{
	vector<Comp> ret; ret.reserve(n);
	for(int i = 0; i != n; ++i) ret.push_back(Comp(v[i], 0));
	return ret;
}
bool fail = 0;
vector<int> convert(vector<Comp> v)
{
	for(int i = 0; i != n; ++i)
		if(fabsl(v[i].imag()) > eps || fabsl(v[i].real() - int(v[i].real() + eps)) > eps)
			return ans;
	vector<int> ret; ret.resize(n);
	for(int i = 0; i != n; ++i)
		ret[i] = int(v[i].real() + eps);
	return ret;
}

vector<Comp> DFT(vector<Comp> vec, bool d)
{
	vector<Comp> ret;
	Comp *arr = vec.data();
	if(d) reverse(arr + 1, arr + n);
	for(int i = 0; i != n; ++i)
	{
		Comp sum = Comp(0, 0), val = Comp(1, 0);
		for(int j = 0; j != n; ++j)
		{
			sum += arr[j] * val;
			val *= w[i];
		}
		ret.push_back(sum);
	}
	if(d) for(int i = 0; i != n; ++i) ret[i] /= n;
	return ret;
}

vector<Comp> arr;
void dfs(int i)
{
	if(i + i > n)
	{
		vector<int> tmp = convert(DFT(arr, 1));
		for(int i = 0; i != n; ++i)
		{
			if(tmp[i] > ans[i]) return;
			if(tmp[i] < ans[i]) {ans = tmp; return;}
		}
		return;
	}
	dfs(i + 1);
	arr[i] = -arr[i]; if(i != n - i) arr[n - i] = -arr[n - i];
	dfs(i + 1);
	arr[i] = -arr[i]; if(i != n - i) arr[n - i] = -arr[n - i];
}


class SplittingFoxes2
{
public:
	vector<int> getPattern(vector<int> res)
	{
		// 给出一个数组，要求将其开方（循环卷积）
		n = res.size();
		ans = vector<int>(n, inf);
		for(int i = 0; i != n; ++i)
			w[i] = Comp(cos(2 * i * pi / n), sin(2 * i * pi / n));
		arr = DFT(convert(res), 0);
		// DFT 循环卷积
		for(int i = 0; i != n; ++i) arr[i] = sqrt(arr[i]);
		dfs(1);
		if(ans[0] >= inf) return vector<int>(1, -1);
		return ans;
	}
}   user;
