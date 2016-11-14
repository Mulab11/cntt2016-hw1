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

using namespace std;
const int MAXN = 54, MAXM = 2525, MOD = 1000000007;
class KingdomAndCities
{
	private:
	int f[MAXN][MAXN];//f[i][j]: i point, j edge, connected graph
	int C[MAXM][MAXN];
    public:
	void init(int limi = MAXM - 1, int limj = MAXN - 1)
	{
		memset(C, 0, sizeof(C));
		for(int i = 0; i <= limi; i++)
		{
			C[i][0] = 1;
			if(i <= limj)
				C[i][i] = 1;
			for(int j = 1; j < i && j <= limj; j++)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
	}
    int howMany(int N, int M, int K)
	{
    	if(K < N - 1 || K > N * (N - 1) / 2)
    		return 0;
    	init();
    	memset(f, 0, sizeof(f));
    	for(int i = 1; i <= N; i++)//O(N^2*K^2)
    		for(int j = 0; j <= K; j++)
    		{
    			f[i][j] = C[i * (i - 1) / 2][j];
    			for(int k = 1; k < i; k++)//Not connected! The first city's group size is k.
    				for(int l = k - 1; l <= k * (k - 1) / 2 && l <= j; l++)//and with l edges.
    					f[i][j] = (f[i][j] - (long long)C[i - 1][k - 1] * f[k][l] % MOD * C[(i - k) * (i - k - 1) / 2][j - l] % MOD + MOD) % MOD;
    			//printf("f[%d][%d] = %d\n", i, j, f[i][j]);
			}
    	if(M == 0)
    		return f[N][K];
    	if(M == 1)
    	{
    		if(N == 1 || K < 2)
    			return 0;
    		int ans = (long long)C[N - 1][2] * f[N - 1][K - 2] % MOD;//1 group
    		for(int i = 1; i <= N - 2; i++)//2 groups, size: i, N - 1 - i
    			for(int j = 0; j <= K - 2; j++)//edge: j, K - 2 - j
    				ans = (ans + (long long)i * (N - 1 - i) * C[N - 2][i - 1] % MOD * f[i][j] % MOD * f[N - 1 - i][K - 2 - j]) % MOD;
    		return ans;
    	}
    	//M == 2
    	if(N == 2 || K < 3)
    		return 0;
    	if(K == 3)
    		return N == 3 ? 1 : N == 4 ? 2 : 0;
    	int ans = (long long)(N - 2) * (N - 2) % MOD * f[N - 2][K - 3] % MOD;//--a--b--, 1 group
    	ans = (ans + (long long)C[N - 2][2] * C[N - 2][2] % MOD * f[N - 2][K - 4]) % MOD;//--a--, --b--, 1 group
    	for(int i = 1; i <= N - 3; i++)//--a--b--, 2 groups, size: i, N - 2 - i
    		for(int j = 0; j <= K - 3; j++)//edge: j, K - 3 - j
    			ans = (ans + (long long)i * (N - 2 - i) * 2 * C[N - 3][i - 1] % MOD * f[i][j] % MOD * f[N - 2 - i][K - 3 - j]) % MOD;
    	for(int i = 1; i <= N - 3; i++)//--a--, --b--, 2 groups, size: i, N - 2 - i
    		for(int j = 0; j <= K - 4; j++)//edge: j, K - 4 - j
    			ans = (ans + (long long)f[i][j] * f[N - 2 - i][K - 4 - j] % MOD * C[N - 3][i - 1] % MOD * i * (N - 2 - i) % MOD/*a-lr*/ * (i * (N - 2 - i)/*b-lr*/ + (C[i][2]/*b-ll*/ + C[N - 2 - i][2]/*b-rr*/) * 2/*swap(a,b)*/)) % MOD;
    	for(int i = 1; i <= N - 4; i++)//--a--, --b--, 3 groups, size: i, ii, N - 2 - i - ii, O(N^2*K^2)
    		for(int j = 0; j <= K - 4; j++)//edge: j, jj, K - 4 - j - jj
    		{
    			const long long tmp = (long long)f[i][j] * C[N - 3][i - 1] % MOD * i % MOD * (N - 2) * 2/*a/b choose any group*/ % MOD;
    			if(!tmp)
    				continue;
    			for(int ii = 1; ii <= N - 3 - i; ii++)
    				for(int jj = 0; jj <= K - 4 - j; jj++)
    					ans = (ans + tmp * f[ii][jj] % MOD * f[N - 2 - i - ii][K - 4 - j - jj] % MOD * C[N - 3 - i][ii - 1] % MOD * ii % MOD * (N - 2 - i - ii)) % MOD;
    		}
        return ans;
    }
};

