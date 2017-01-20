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

int n;

class BallsSeparating {
    public:
    int minOperations(vector<int> r, vector<int> g, vector<int> b) {
		int Ans = 2e9;
		int sum = 0;
		n = r.size();
		if (n < 3) return -1;//如果小于三个盒子，一定无解
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < n; ++k) {//最终3种颜色的盒子每个至少要有一个
					sum = 0;
					if (i != j && j != k && i != k) {
						for (int p = 0; p < n; ++p) {
							if (p == i) sum += g[p] + b[p];
							else if (p == j) sum += r[p] + b[p];
							else if (p == k) sum += r[p] + g[p];
							else sum += min(r[p] + g[p], b[p] + min(r[p], g[p]));//统计代价
						}
						Ans = min(Ans, sum);//更新答案
					}
				}
			}
		}
        return Ans;
    }
};
