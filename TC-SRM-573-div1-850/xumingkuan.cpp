#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
const int MOD = 1000000007;
long long quickmul(int a, int b)
{
	if(b <= 1)
		return b ? a : 1;
	long long tmp = quickmul(a, b >> 1);
	tmp = tmp * tmp % MOD;
	return b & 1 ? tmp * a % MOD : tmp;
}
class WolfPack
{
private:
	int n, m;
	int Cm[101010];//Cm[i] = C(m, i)
	void convert(int &x, int &y)
	{
		int xx = x, yy = y;
		x = xx + yy, y = xx - yy;
	}
	int solve(vector<int> x)//1-D problem
	{
		sort(x.begin(), x.end());
		int ans = 0;
		for(int i = x.back() - m; i <= x.front() + m; i += 2)
		{
			long long now = 1;
			for(int j = 0; j < n; j++)
				now = now * Cm[(m - abs(x[j] - i)) >> 1] % MOD;
			ans = (ans + now) % MOD;
		}
		return ans;
	}
public:
	int calc(vector<int> x, vector<int> y, int m)
	{
		n = x.size();
		this->m = m;
		int tmp = (x[0] + y[0]) & 1;
		for(int i = 0; i < n; i++)
		{
			if(((x[i] + y[i]) & 1) != tmp)//ji ou xing bu dui
				return 0;
			convert(x[i], y[i]);
		}
		Cm[0] = 1;
		for(int i = 1; i <= m; i++)
			Cm[i] = (long long)Cm[i - 1] * (m - i + 1) % MOD * quickmul(i, MOD - 2) % MOD;
		int ansx = solve(x);
		int ansy = solve(y);
		int ans = (long long)ansx * ansy % MOD;
		return ans;
	}
};

