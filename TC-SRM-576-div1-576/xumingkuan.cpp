#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1000000009;

class TheExperiment
{
private:
	int n;
	string a;//intensity
	int sum[303];//prefix sum of a, 1-based
	int f[303][303][3];//f[i][j][k]: i sponges, interval [0, j), number of ways;
	//f[i][j][0]: the last sponge is at [j - x, j) && (x == L || it's covered by another L-length sponge either directly or indirectly)
	//f[i][j][1]: \sum_{j1=0}^j {f[i][j1][0]}
	//f[i][j][2]: f[i][j][1] + (the last sponge is at [j - x, j) && x < L && it's NOT covered by any other L-length sponges either directly or indirectly (then there must be a sponge at [j, j + y) ) )
	bool ok[303][303];//ok[i][j] = if sum of interval [i, j) is in [A, B]
public:
	int countPlacements(vector<string> intensity, int M, int L, int A, int B)
	{
		a.clear();
		for(int i = 0; i < intensity.size(); i++)
			a += intensity[i];
		n = a.size();
		sum[0] = 0;
		for(int i = 1; i <= n; i++)
			sum[i] = sum[i - 1] + (a[i - 1] -= '0');
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j <= n; j++)
				ok[i][j] = (sum[j] - sum[i] >= A && sum[j] - sum[i] <= B);
		memset(f, 0, sizeof(f));
		for(int i = 0; i <= n; i++)
			f[0][i][2] = 1;
		for(int i = 1; i <= M; i++)
			for(int j = i; j <= n; j++)
			{
				long long now = 0;
				if(j >= L && ok[j - L][j])
					now += f[i - 1][j - L][2];
				for(int k = 1; k <= j && k < L; k++)
					if(ok[j - k][j])
						now += f[i - 1][j - k][0];
				f[i][j][0] = now % MOD;
				now += f[i][j - 1][1];
				f[i][j][1] = now % MOD;
				for(int k = 1; k <= j && k < L; k++)
					if(ok[j - k][j])
						now += f[i - 1][j - k][2] - f[i - 1][j - k][0];
				f[i][j][2] = now % MOD;
				//printf("f[%d][%d] = %d %d %d\n", i, j, f[i][j][0], f[i][j][1], f[i][j][2]);
			}
		return f[M][n][1];
	}
};

