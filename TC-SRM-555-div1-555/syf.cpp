//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <iostream>
#include<cstring>

using namespace std;

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define mod 555555555

class XorBoard{
public:
	int C[3505][3505];

	int count(int H, int W, int Rcount, int Ccount, int S) {
		//prepare the values of combination
		memset(C, 0, sizeof(C));
		FOR (i, 0, 3500) {
			C[i][0] = 1;
			FOR (j, 1, i)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}

		long long res = 0;

		//x rows and y columns will be fliped the odd number of times
		FOR (x, 0, min(H, Rcount))
		if (((Rcount - x) % 2) == 0)
			FOR (y, 0, min(W, Ccount))
			if (((Ccount - y) % 2) == 0)
				//this condition ensures there will be exactly S '1's after all
				if (W * x + H * y - 2 * x * y == S) {
					long long tmp;
					//the number of ways flipping rows Rcount times and x rows were flipped by an odd number of times
					tmp = (long long) C[H][x] * C[H + (Rcount - x) / 2 - 1][H - 1] % mod;

					//mutiplied by the number of ways flipping columns Rcount times and y rows were flipped by an odd number of times
					tmp = tmp * C[W][y] % mod;
					tmp = tmp * C[W + (Ccount - y) / 2 - 1][W - 1] % mod;

					//add tmp to result
					res = (res + tmp) % mod;
				}

		res = (res + mod) % mod;

		return res;
	}
};