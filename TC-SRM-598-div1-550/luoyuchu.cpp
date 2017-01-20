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

class FoxAndFencing {
    public:
    string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) {
		if (d <= mov1 + rng1) return "Ciel";//如果一开始就能攻击到
		if (mov1 + rng1 == mov2 + rng2) return "Draw";//如果范围同等，则一定平局
		if (mov1 + rng1 < mov2 + rng2) {//对于范围更大的选手，如果要成功攻击一定时先到达对手范围+1的地方，然后对手会逃跑，然后自己移动并攻击
			if (mov1 + d <= mov2 + rng2) return "Liss";
			else if ((mov2 > mov1 || mov2 + mov1 + rng1 + 1 >= d + mov1) && mov1 + rng1 + mov1 < mov2 + rng2) return "Liss";
			else return "Draw";
		}
		else {
			if ((mov1 > mov2 || mov1 + mov2 + rng2 + 1 >= d) && mov2 + rng2 + mov2 < mov1 + rng1) return "Ciel";
			else return "Draw";
		}
    }
};
