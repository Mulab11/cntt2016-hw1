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

class LISNumber
{
private:
	int f[40][1300];//f[i][j]: cards with number in range [0, i), LISNumber = j, number of different valid sequences
	int C[1300][40];
	void init(int n, int m)
	{
		memset(C, 0, sizeof(C));
		for(int i = 0; i <= n; i++)
		{
			C[i][0] = 1;
			if(i <= m)
				C[i][i] = 1;
			for(int j = 1; j < i && j <= m; j++)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
	}
public:
	int count(vector<int> cardsnum, int K)
	{
		const int n = cardsnum.size();
		init(36 * 36, 36);
		int prev = 0;//number of cards with number in range [0, i - 1)
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(int i = 1; i <= n; i++)
		{
			const int now = cardsnum[i - 1];
			for(int j = 0; j <= prev && j <= K; j++)
				if(f[i - 1][j])
					for(int k = max(now - j, 0); k <= now && j + k <= K; k++)//C[j][now - k]: choose 'now-k' of 'j' places to put cards; C[prev + now - j][k]: put the remaining 'k' cards into '(prev+now)-(j+k)+1' places
						f[i][j + k] = (f[i][j + k] + (long long)f[i - 1][j] * C[j][now - k] % MOD * C[prev + now - j][k]) % MOD;
			prev += now;
//			for(int j = 0; j <= prev && j <= K; j++)
//				if(f[i][j])
//					printf("f[%d][%d] = %d\n", i, j, f[i][j]);
		}
		return f[n][K];
	}
};

