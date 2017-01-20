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

class TheBrickTowerEasyDivOne {
    public:
    int find(int rc, int rh, int bc, int bh) {
		int Ans;
		Ckmin(rc, bc + 1);//多出的砖头无意义
		Ckmin(bc, rc + 1);
		if (rh == bh) {//如果两种高度一样，那么只有砖头块数的区别
			Ans = rc + bc;
		}
		else {
			Ans = min(rc, bc) * 3;//否则可能两种颜色一样，红色多一个，蓝色多一个
			if (rc != bc) Ans += 1;//如果有一种砖头多了，可以再放一个
		}
        return Ans;
    }
};
