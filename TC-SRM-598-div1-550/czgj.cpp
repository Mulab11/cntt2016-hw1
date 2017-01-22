/*
	Fen Lei Tao Lun
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class FoxAndFencing {
	public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) {
		if (d <= mov1 + rng1) return "Ciel";
		if (d + mov1 <= mov2 + rng2) return "Liss";
		if (mov1 + rng1 > 2 * mov2 + rng2 && mov1 > mov2) return "Ciel";
		if (mov2 + rng2 > 2 * mov1 + rng1 && mov2 > mov1) return "Liss";
		return "Draw";
	}
};

/*
	Long time no see an O(1) 500-problem
*/
