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
typedef long long LL;
typedef pair<int, int> pii;

class FoxAndFencing {
public :
	//分类讨论，细心题，博弈
	string WhoCanWin(int m1, int m2, int r1, int r2, int dis) {
		if (dis <= m1 + r1) {
			return "Ciel";		//一步胜利
		} else if (dis + m1 <= m2 + r2) {
			return "Liss";		//第二步胜利
		} else if (m1 > m2 && (m2 * 2 + r2 < m1 + r1)) {
			return "Ciel";		//C 追赶 L
		} else if (m2 > m1 && (m1 * 2 + r1 < m2 + r2)) {
			return "Liss";		//L 追赶 C
		} else {
			return "Draw";		//平局
		}
	};
};
