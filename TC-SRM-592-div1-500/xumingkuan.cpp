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
const int MOD = 1000000007;

class LittleElephantAndPermutationDiv1
{
private:
	int f[2][52][2000];//f[i & 1][j][k]: put j of i numbers (1~i) into places i+1~N, sum of {max(a[x], x) | max(a[x], x) <= i} = k, number of ways
public:
	int getNumber(int N, int K)
	{
		memset(f, 0, sizeof(f));
		f[0][0][0] = 1;
		for(int i = 1; i <= N; i++)
		{
			memset(f[i & 1], 0, sizeof(f[i & 1]));
			int mxk = i * i * 3 / 4, tmp;
			for(int j = 0; j < i; j++)
				for(int k = 0; k <= mxk; k++)
					if((tmp = f[~i & 1][j][k]))
					{
						#define add(x, y) x = (x + y) % MOD
						if(j)
							add(f[i & 1][j - 1][k + i * 2], (long long)tmp * j * j);//a[i] < i, a[<i] = i
						add(f[i & 1][j][k + i], (long long)tmp * (2 * j + 1));//a[i] < i, a[>i] = i //a[i] = i //a[i] > i, a[<i] = i
						add(f[i & 1][j + 1][k], tmp);//a[i] > i, a[>i] = i
					}
			/*for(int j = 0; j <= i; j++)
				for(int k = 0; k <= mxk[i & 1]; k++)
					if(f[i & 1][j][k])
						printf("f[%d][%d][%d] = %d\n", i, j, k, f[i & 1][j][k]);*/
		}
		long long ans = 0;
		for(int i = K; i <= (N + 1) * (N + 1) * 3 / 4; i++)
			ans += f[N & 1][0][i];
		for(int i = 1; i <= N; i++)//* N!
			ans = ans * i % MOD;
		return (int)ans;
	}
};

