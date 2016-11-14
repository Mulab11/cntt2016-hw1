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
const int MOD = 555555555;

class XorBoard
{
	private:
	int C[2400][1600];//combination
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
	int count(int H, int W, int Rcount, int Ccount, int S)
	{
		init(max((Rcount >> 1) + H, (Ccount >> 1) + W), max(H, W));
		int ans = 0;
		for(int r = (Rcount & 1); r <= H && r <= Rcount; r += 2)//flip r rows
			for(int c = (Ccount & 1); c <= W && c <= Ccount; c += 2)//flip c columns
				if(r * (W - c) + c * (H - r) == S)//ok (in fact only <= min(H, W) pairs of (r, c) are ok)
					ans = (ans + (long long)C[H][r] * C[((Rcount - r) >> 1) + H - 1][H - 1] % MOD * C[W][c] % MOD * C[((Ccount - c) >> 1) + W - 1][W - 1]) % MOD;
		return ans;
	}
};

