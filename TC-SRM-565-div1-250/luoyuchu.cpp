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

const int maxn = 55;

int n;
LL f[maxn][maxn * 3];//f[i][j]表示现在走到了第i个怪物， 已经花费j块钱所能达到的dread的最大值，

class MonstersValley {
    public:
    int minimumPrice(vector<long long> dread, vector<int> price) {
		memset(f, -0x3f, sizeof(f));//负数表示用j快钱不能到达这一位置
		f[0][0] = 0;
		for (int i = 1; i <= dread.size(); ++i) {
			for (int j = 0; j < maxn * 3; ++j) {
				if (f[i - 1][j] < 0) continue;
				Ckmax(f[i][j + price[i - 1]], f[i - 1][j] + dread[i - 1]);//选择这一个怪物
				if (f[i - 1][j] >= dread[i - 1]) Ckmax(f[i][j], f[i - 1][j]);//可以不选
			}
		}
		for (int i = 0; i < maxn * 3; ++i) {
			if (f[dread.size()][i] >= 0) {
				return i;//找到最小的能够走到最后一个怪物的代价
			}
		}
    }
};

