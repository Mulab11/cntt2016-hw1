#include <bits/stdc++.h>

using namespace std;


class FoxAndFencing{
	public:
		string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d){
			if (mov1+rng1 >= d) return "Ciel";
			if (mov1+rng1 == mov2+rng2) return "Draw";
			if (mov1+rng1 > mov2+rng2){
				if (mov1>mov2 && mov2+rng2+mov2 < mov1+rng1) return "Ciel";
				else return "Draw"; 
			}
			else{
				if (d+mov1 <= mov2+rng2) return "Liss";//注意要判断一开始能不能获胜 
				else if (mov2>mov1 && mov1+rng1+mov1 < mov2+rng2) return "Liss";
				else return "Draw";
			}
		}
};
