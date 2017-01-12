#include <bits/stdc++.h>

using namespace std;

const int maxn = 100005,mo = int(1e9) + 7;

class WolfPack
{
public:
	int fac[maxn],rfac[maxn];

	int pow(int a,int b)
	{
		int tmp = 1;
		for(;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int get_c(int n,int m) //calc c(n,m)
	{
		if (n < 0 || m < 0 || m > n) return 0;
		return fac[n] * 1ll * rfac[m] % mo * rfac[n - m] % mo;
	}

	int m;

	int solve(vector<int> x)
	{
		int ans = 0;
		for(int fx = -300000;fx <= 300000;fx ++) //the biggest |x| we can get is 10^5 * 3 = 300000
		{
			int cur = 1;
			for(int i = 0;i < x.size();i ++)
			{
				int v = m + fx - x[i],a = v / 2,b = m - a;
				if ((v & 1) || a < 0 || b < 0 || a > m || b > m) {cur = 0;break;} //illegal situation
				cur = cur * 1ll * get_c(m,a) % mo;
			}
			ans = (ans + cur) % mo;
		}
		return ans;
	}

	int calc(vector<int> x, vector<int> y, int M)
	{
		m = M;
		vector<int> nx,ny;
		int n = x.size();
		for(int i = 0;i < n;i ++)
			nx.push_back(x[i] + y[i]),ny.push_back(x[i] - y[i]);//rotate the coordinate
		//now x and y are independent
		fac[0] = 1;
		for(int i = 1;i <= m;i ++) fac[i] = fac[i - 1] * 1ll * i % mo;
		rfac[m] = pow(fac[m],mo - 2);
		for(int i = m;i;i --) rfac[i - 1] = rfac[i] * 1ll * i % mo;
		return solve(nx) * 1ll * solve(ny) % mo;
	}
};
