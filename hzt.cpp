#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#define Rep(i, x, y) for (int i = x; i <= y; i ++)
#define Dwn(i, x, y) for (int i = x; i >= y; i --)
#define RepE(i, x) for(int i = pos[x]; i; i = g[i].nex)
using namespace std;
typedef long long ll;
typedef double db;
const int mod = 1000000007, N = 52;
int f[N][N][N * N];
class LittleElephantAndPermutationDiv1 {
public:
	int getNumber(int n, int m) {
		f[0][0][0] = 1;
		Rep(i, 1, n) {
			Rep(j, 0, i) {
				Rep(k, 0, m) {
					ll z = f[i - 1][j][k];
					(f[i][j][min(m, k + i)] += (2 * j + 1) * z % mod) %= mod;
					/*
						将数i填在下标为i处
						将数i填在下标小于i处，下标为i处填入了大于i的数
						将数i填在下标大于i处，下标为i处填入了小于i的数
						可以把这三种情况合并
					*/
					(f[i][j + 1][k] += z) %= mod;
					// 将数i填在下标大于i处，下标为i处填入了大于i的数
					if (j) (f[i][j - 1][min(m, k + 2 * i)] += z * j * j % mod) %= mod;
					// 将数i填在下标小于i处，下标为i处填入了小于i的数
				}
			}
		}
		ll ans = f[n][0][m];
		Rep(i, 1, n) ans = ans * i % mod;
		return ans;
	}
};