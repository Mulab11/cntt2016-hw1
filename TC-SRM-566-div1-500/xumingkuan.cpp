#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
const int MOD = 1000000007;
class PenguinEmperor
{
	private:
	int n;
	int f[400][400];//f[i][j]: city 0 --- i days --> city j
	int u[70][400];//for quickmul
	int ans[400], tmp[400];
	void update(int *c, const int *a, const int *b)//c = a * b;
	{
		memset(c, 0, n * sizeof(int));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				c[(i + j) % n] = (c[(i + j) % n] + (long long)a[i] * b[j]) % MOD;
	}
	public:
	int countJourneys(int numCities, long long daysPassed)
	{
		n = numCities;
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(int i = 1; i < n; i++)
			if(i * 2 == n)//(j - i + n) % n == (j + i) % n
				for(int j = 0; j < n; j++)
					f[i][j] = f[i - 1][(j + i) % n];
			else
				for(int j = 0; j < n; j++)
					f[i][j] = (f[i - 1][(j - i + n) % n] + f[i - 1][(j + i) % n]) % MOD;
		memcpy(u[0], f[n - 1], n * sizeof(int));
		long long num = daysPassed / n;
		memcpy(ans, (num & 1 ? u[0] : f[0]), n * sizeof(int));
		for(int i = 1; (1ll << i) <= num; i++)
		{
			update(u[i], u[i - 1], u[i - 1]);
			if(num & (1ll << i))
			{
				update(tmp, ans, u[i]);
				memcpy(ans, tmp, n * sizeof(int));
			}
		}
		update(tmp, ans, f[daysPassed % n]);
		return tmp[0];
	}
};

