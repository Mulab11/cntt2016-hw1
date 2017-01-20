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

LL D(int x, int y)//计算x个一样的物品分给y个人，每个人可以拿0个的方案数
{
	LL S = 1;
	x += y - 1;
	for (int i = 0; i < y - 1; ++i) {
		S = S * (x - i); 
	}
	return S / (y - 1);
}

class AlternateColors2 {
    public:
    long long countWays(int n, int k) {
		int m1, m2;
		LL Ans = 0;
		for (int i = 0; i <= n / 3; ++i) {//枚举一开始的RGB轮流放的序列的长度
			m1 = i * 3;
			if (k <= m1) {
				if (k % 3 == 1) {//如果k被枚举的覆盖，后面随意放
					Ans += D(n - m1, 2) * 3;
					if (D(n - m1, 2) > 1) Ans -= 3;//由于后面全部都是一种颜色而多算的
					else if (D(n - m1, 2) == 1) Ans -= 2;//假如后面只有0个球而多算的
				}
			}
			else {
				if ((k - m1) % 2 == 1) {//如果k在两个两个删除的部分
					Ans += D(n - m1 - (k - m1 + 1), 2) * 2;
				}
				Ans += ((n - m1 - (n - k + 1)) / 2 + 1) * 2;//如果k在最后只删一个颜色的部分
				--Ans;
			}
		}
		return Ans;
    }
};

