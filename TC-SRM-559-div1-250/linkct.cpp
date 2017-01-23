#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class HyperKnight{
public:
	int bc[265], minx, miny, maxx, maxy, C[15][15];
	LL countCells(int a, int b, int n, int m, int k){
		int dx[] = {a, a, -a, -a, b, b, -b, -b}, dy[] = {b, -b, b, -b, a, -a, a, -a}, i, j;
		LL ans = 0; bc[0] = 0;
		for(i = 0; i <= 8; ++ i)
			for(j = C[i][0] = C[i][i] = 1; j < i; ++ j)
				C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		for(i = 0; i < 256; ++ i){
			bc[i] = bc[i >> 1] + (i & 1);
			if(bc[i] < k) continue;
			minx = miny = 1, maxx = n, maxy = m;
			for(j = 0; j < 8; ++ j)
				if(i & (1 << j)){
					minx = max(minx, 1 - dx[j]);
					maxx = min(maxx, n - dx[j]);
					miny = max(miny, 1 - dy[j]);
					maxy = min(maxy, m - dy[j]);
				}
			if(minx > maxx || miny > maxy) continue;
			if((bc[i] - k) & 1) ans -= C[bc[i]][k] * LL(maxx - minx + 1) * (maxy - miny + 1);
			else ans += C[bc[i]][k] * LL(maxx - minx + 1) * (maxy - miny + 1);
		} return ans;
	}
};
