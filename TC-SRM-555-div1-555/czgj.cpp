/*
	Easy combinatorics.
	Be careful not to get MLE = =
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD = 555555555;
int C[2550][2550];
class XorBoard {
	public:
	void init(){
		for (int i = 0; i <= 2500; ++i)
			for (int j = 0; j <= i; ++j)
				C[i][j] = j ? (C[i - 1][j] + C[i - 1][j - 1]) % MOD : 1;
	}
	int calc(int H, int W, int Rc, int Cc, int x, int y){
		// (For Rows) we get (Rc - x) extra flips, and they should be in pairs, distributed in all H rows.
		return ((LL)C[H][x] * C[(Rc - x) / 2 + H - 1][H - 1] % MOD) * ((LL)C[W][y] * C[(Cc - y) / 2 + W - 1][W - 1] % MOD) % MOD;
	}
	int count(int H, int W, int Rcount, int Ccount, int S) {
		init();
		int ret = 0;
		for (int i = 0; i <= Rcount; ++i)
			for (int j = 0; j <= Ccount; ++j)
				if ((Rcount - i) % 2 == 0 && (Ccount - j) % 2 == 0 && i * W + j * H - 2 * i * j == S)
					ret = (ret + calc(H, W, Rcount, Ccount, i, j)) % MOD;
		return ret;
	}
};

/*
	Ima wa tada sore wo negai tsudukeru...
		- you
*/
