#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

class HyperKnight {
    public:
    long long countCells(int a, int b, int nr, int nc, int k) {
    	LL f[19] = {0}, g[19] = {0};//f[i]表示至少有i种走法可行的方案数，g[i]为恰好有i种走法可行的方案数
    	int C[19][19] = {0};
    	int walk[19][2] = {0}, wt = 0;
    	for (int i = 0; i <= 8; ++i) {//预处理组合数
    		C[i][0] = 1;
    		for (int j = 1; j <= i; ++j) {
    			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    		}
    	}
    	for (int i = -1; i <= 1; ++i) {//求出8中走法
    		for (int j = -1; j <= 1; ++j) {
    			if (i != 0 && j != 0) {
    				walk[++wt][0] = i * a;
    				walk[wt][1] = j * b;
    				walk[++wt][0] = i * b;
    				walk[wt][1] = j * a;
    			}
    		}
    	}
    	int N = (1 << 8);
    	int tmp, cnt;
    	int Lx, Rx, Ly, Ry;
    	for (int i = 0; i < N; ++i) {//枚举那些走法一定可行
    		tmp = i;
    		cnt = 0;
    		Lx = Ly = 1;
    		Rx = nr; Ry = nc;
    		for (int j = 1; j <= 8; ++j) {
    			if (tmp & 1) {
    				++cnt;
    				Ckmin(Rx, nr - walk[j][0]);
    				Ckmax(Lx, 1-walk[j][0]);
    				Ckmin(Ry, nc - walk[j][1]);
    				Ckmax(Ly, 1-walk[j][1]);
    			}
    			tmp >>= 1;
    		}
    		if (Rx < Lx || Ry < Ly) continue;
			f[cnt] += (LL)(Rx - Lx + 1) * (Ry - Ly + 1);
    	}
    	for (int i = 8; i >= 0; --i) {//容斥原理用f[i]求g[i]
    		g[i] = f[i];
    		for (int j = i + 1; j <= 8; ++j) {
    			g[i] -= C[j][i] * g[j];
    		}
    	}
        return g[k];//答案为g[k]
    }
};

