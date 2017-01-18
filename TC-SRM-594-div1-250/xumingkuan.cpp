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
using namespace std;

class AstronomicalRecords
{
private:
	int n, m;//A.size(), B.size()
	vector<int> a, b;//A, B
	int f[55][55];//f[i][j]: max match of A[0, i) and B[0, j)
	int solve(int u, int v)
	{
		memset(f, 0, sizeof(f));
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if((long long)a[i - 1] * v == (long long)b[j - 1] * u)
					f[i][j] = f[i - 1][j - 1] + 1;
				else
					f[i][j] = max(f[i - 1][j], f[i][j - 1]);
		return n + m - f[n][m];
	}
public:
	int minimalPlanets(vector<int> A, vector<int> B)
	{
		n = (a = A).size(), m = (b = B).size();
		int ans = n + m;
		for(int i = 0; i < n; i++)//enum the ratio A:B
			for(int j = 0; j < m; j++)
				ans = min(ans, solve(a[i], b[j]));
		return ans;
	}
};

