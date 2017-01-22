/*
	Easy math.
	With Inclusion-Exclusion Principle.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int dx[8], dy[8];
LL sum[256];
class HyperKnight {
	public:
	LL countCells(int a, int b, int numRows, int numColumns, int k) {
		dx[0] = dx[1] = a, dx[2] = dx[3] = b, dx[4] = dx[5] = -a, dx[6] = dx[7] = -b;
		dy[0] = dy[4] = b, dy[1] = dy[5] = -b, dy[2] = dy[6] = a, dy[3] = dy[7] = -a;
		LL ret = 0;
		for (int i = 0; i < 256; ++i) { // go over all sets of moves
			int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			for (int j = 0; j < 8; ++j) if (i >> j & 1){
				x1 = min(x1, dx[j]); x2 = max(x2, dx[j]);
				y1 = min(y1, dy[j]); y2 = max(y2, dy[j]);
			}
			sum[i] = (LL)max(0, numRows - (x2 - x1)) * max(0, numColumns - (y2 - y1));
		}
		for (int i = 0; i < 8; ++i) // Inclusion-Exclusion or Subset Inversion(?)
			for (int j = 0; j < 256; ++j) if (~j >> i & 1)
				sum[j] -= sum[j | 1 << i];
		for (int i = 0; i < 256; ++i) if (__builtin_popcount(i) == k) ret += sum[i]; // Find the answer
		return ret;
	}
};

/*
	Itsumatemo Itsumatemo
	Mamotteyuku
		- Toki wo Kizamu Uta
*/
