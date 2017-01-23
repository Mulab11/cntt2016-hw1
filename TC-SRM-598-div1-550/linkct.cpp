#include <bits/stdc++.h>
using namespace std;

class FoxAndFencing{
public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d){
		if(mov1 + rng1 >= d) return "Ciel";
		int threat1 = mov1 + rng1, threat2 = mov2 + rng2;
		if(threat1 == threat2) return "Draw";
		if(threat1 > threat2)
			return mov1 > mov2 && threat2 + mov2 + 1 <= threat1 ? "Ciel" : "Draw";
		if(d + mov1 <= threat2) return "Liss";
		return mov2 > mov1 && threat1 + mov1 + 1 <= threat2 ? "Liss" : "Draw";
	}
};
