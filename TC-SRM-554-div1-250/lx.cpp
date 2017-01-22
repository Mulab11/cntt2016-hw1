#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;

class TheBrickTowerEasyDivOne {
public :
	//数学，计数
	int find(int rC, int rH, int bC, int bH) {
		return min(rC, bC) * (rH == bH ? 2 : 3) + (rC != bC);
	}
};

