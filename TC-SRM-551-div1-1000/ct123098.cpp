#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 40 + 10;

class SweetFruits
{
	public:

	int n, m, maxS;
	vector<int> s;
	int f[MAXN], g[MAXN];
	int c[MAXN][MAXN];

	void calcC()
	{
		for(int i = 0; i <= n; i++)
		{
			c[i][0] = c[i][i] = 1;
			for(int j = 1; j <= i - 1; j++)
				c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
		}
	}

	void calcF()
	{
		vector<int> sum[2][MAXN];
		sum[0][0].push_back(0);
		for(int i = 0; i < m / 2; i++)
			if(s[i] != -1)
				for(int j = m; j >= 1; j--)
					for(int k = 0; k < sum[0][j - 1].size(); k++)
						sum[0][j].push_back(sum[0][j - 1][k] + s[i]);
		sum[1][0].push_back(0);
		for(int i = m / 2; i < m; i++)
			if(s[i] != -1)
				for(int j = m; j >= 1; j--)
					for(int k = 0; k < sum[1][j - 1].size(); k++)
						sum[1][j].push_back(sum[1][j - 1][k] + s[i]);
		for(int i = 0; i <= 1; i++)
			for(int j = 0; j <= m; j++)
				sort(sum[i][j].begin(), sum[i][j].end());
		for(int i = 0; i <= m; i++)
			for(int j = 0; j <= i; j++)
			{
				int p = sum[1][i - j].size();
				for(int k = 0; k < sum[0][j].size(); k++)
				{
					while(p > 0 && sum[0][j][k] + sum[1][i - j][p - 1] > maxS)
						p--;
					f[i] = (f[i] + p) % MOD;
				}
			}
		// for(int i = 0; i <= m; i++)
		// 	cout << f[i] << endl;
		// cout << sum[0][0].size() << ' ' << sum[1][0].size() << endl;
	}

	int fpow(int a, int p)
	{
		if(p == 0) return 1;
		int tmp = fpow(a, p / 2);
		tmp = (long long)tmp * tmp % MOD;
		if(p & 1) return (long long)tmp * a % MOD;
		else return tmp;
	}

	int inv(int a)
	{
		return fpow(a, MOD - 2);
	}

	int det(int n, int a[][MAXN])
	{
		int ret = 1;
		for(int i = 1; i <= n; i++)
		{
			for(int j = i; j <= n; j++)
				if(a[j][i] != 0)
				{
					if(j != i)
						swap(a[i], a[j]), ret *= -1;
					break;
				}
			if(a[i][i] == 0) return 0;
			for(int j = i + 1; j <= n; j++)
				if(a[j][i] != 0)
				{
					int lam = (MOD - (long long)a[j][i] * inv(a[i][i]) % MOD) % MOD;
					for(int k = i; k <= n; k++)
						a[j][k] = (a[j][k] + (long long)lam * a[i][k] % MOD) % MOD;
				}
		}
		for(int i = 1; i <= n; i++)
			ret = (long long)ret * a[i][i] % MOD;
		ret = (ret + MOD) % MOD;
		return ret;
	}

	void calcG()
	{
		for(int i = 0; i <= m; i++)
		{
			int e[MAXN][MAXN], a[MAXN][MAXN];
			memset(e, 0, sizeof(e));
			memset(a, 0, sizeof(a));
			for(int j = 1; j <= i; j++)
				for(int k = m + 1; k <= n; k++)
					e[j][k] = e[k][j] = true;
			for(int j = i + 1; j <= m; j++)
				for(int k = m + 1; k <= n; k++)
					e[j][k] = e[k][j] = true;
			for(int j = 1; j <= i; j++)
				for(int k = 1; k <= i; k++)
					if(j != k)
						e[j][k] = true;
			for(int j = m + 1; j <= n; j++)
				for(int k = m + 1; k <= n; k++)
					if(j != k)	
						e[j][k] = true;

			for(int j = 1; j <= n; j++)
				for(int k = 1; k <= n; k++)
					a[j][j] += e[j][k];
			for(int j = 1; j <= n; j++)
				for(int k = 1; k <= n; k++)
					a[j][k] -= e[j][k];
			// for(int j = 1; j <= n; j++)
			// {
			// 	for(int k = 1; k <= n; k++)
			// 		cout << a[j][k] << ' ';
			// 	cout << endl;
			// }
			g[i] = det(n - 1, a);
			for(int j = 0; j <= i - 1; j++)
				g[i] = (g[i] - (long long)c[i][j] * g[j] % MOD + MOD) % MOD;
			// cout << g[i] << endl;
		}
	}

	int countTrees(vector<int> sweetness, int maxSweetness)
	{
		sort(sweetness.begin(), sweetness.end(), greater<int>());
		m = n = sweetness.size();
		s = sweetness;
		maxS = maxSweetness;
		for(int i = 0; i < n; i++)
			if(s[i] == -1)
			{
				m = i; break;
			}

		calcC();
		calcF();
		calcG();
		int ans = 0;
		for(int i = 0; i <= n; i++)
			ans = (ans + (long long)f[i] * g[i] % MOD) % MOD;
		
		return ans;
	}
};

