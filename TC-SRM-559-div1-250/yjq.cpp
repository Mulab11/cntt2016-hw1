#include <bits/stdc++.h>

using namespace std;

typedef long long LL ; 



bool Inboard(int x, int y, int n, int m) {
		return x >= 0 && x < n && y >= 0 && y < m;
}

class HyperKnight {
		public:
				LL countCells(int a, int b, int n, int m, int k) {
						int gx[6] = {0, a, b, n - a, n - b, n}, gy[6] = {0, a, b, m - a, m - b, m};

						int dgx[8] = {a, a, -a, -a, b, b, -b, -b}, dgy[8] = {b, -b, b, -b, a, -a, a, -a};
						sort(gx, gx + 6);
						sort(gy, gy + 6);
						LL ans = 0;
						for(int i = 0; i < 5; i ++) {
								for(int j = 0; j < 5; j ++) {
										int cnt = 0;
										for(int t = 0; t < 8; t ++) cnt += Inboard(gx[i] + dgx[t], gy[j] + dgy[t], n, m);
										if(cnt == k)
												ans += (LL)(gx[i + 1] - gx[i]) * (gy[j + 1] - gy[j]);
								}
						}
						return ans;
				}
};
