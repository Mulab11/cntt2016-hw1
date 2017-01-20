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

const int walk[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int gcd(int x, int y)//求最大公约数
{
	while (y) {
		y ^= x ^= y ^= x %= y;
	}
	return x;
}

void Go(LL &x, LL &y, int &dir, vector<int> a)//模拟一次运行过程
{
	for (int i = 0; i < (int)a.size(); ++i) {
		x += walk[dir][0] * a[i];
		y += walk[dir][1] * a[i];
		dir = (dir + a[i]) % 4;
	}
}

class RobotHerb {
    public:
    long long getdist(int T, vector<int> a) {
		int dir = 0, period;
		LL x = 0, y = 0;
		LL Ans[2] = {0};
		for (int i = 0; i < (int)a.size(); ++i) {
			x += walk[dir][0] * a[i];
			y += walk[dir][1] * a[i];
			dir = (dir + a[i]) % 4;
		}
		period = 4 / gcd(4, dir);//按照方向的变化求出周期
		x = 0;
		y = 0;
		dir = 0;
		for (int i = 1; i <= period; ++i) {
			Go(x, y, dir, a);
		}
		Ans[0] += x * (T / period);
		Ans[1] += y * (T / period);//所有整周期的变化
		x = 0;
		y = 0;
		dir = 0;
		for (int i = 1; i <= T % period; ++i) {//对于剩余的暴力模拟
			Go(x, y, dir, a);
		}
		Ans[0] += x;
		Ans[1] += y;
        return abs(Ans[0]) + abs(Ans[1]);
    }
};
