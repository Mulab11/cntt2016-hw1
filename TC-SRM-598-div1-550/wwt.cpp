#include <bits/stdc++.h>

using namespace std;

class FoxAndFencing
{
public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
	{
		if (d <= mov1 + rng1) return "Ciel"; //first attack
		if (d + mov1 <= mov2 + rng2) return "Liss"; //second attack
		//assume a stands at p,b stands at q,and a beats b
		//q - p > mov2 + r2
		//q + mov2 <= p + mov1 + r1--->mov1 + r1 > mov2 * 2 + r2
		//mov1 > mov2
		if (mov1 > mov2 && mov1 + rng1 > mov2 * 2 + rng2) return "Ciel";
		if (mov2 > mov1 && mov2 + rng2 > mov1 * 2 + rng1) return "Liss";
		return "Draw";
	}
};
