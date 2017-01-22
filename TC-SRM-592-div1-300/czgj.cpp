/*
	Greedy for every turn.
*/

#include <bits/stdc++.h>
using namespace std;

class LittleElephantAndBalls {
	public:
	int score(string S){ // Count distinct colors in S
		bool R = 0, G = 0, B = 0;
		for (int i = 0; i < S.length(); ++i){
			if (S[i] == 'R') R = 1;
			if (S[i] == 'G') G = 1;
			if (S[i] == 'B') B = 1;
		}
		return R + G + B;
	}
	int getNumber(string S) {
		string now; int n = S.length(), ret = 0;
		for (int i = 0; i < n; ++i){
			int mx = -1, id = -1;
			for (int j = 0; j <= i; ++j){
				int t = score(string(now, 0, j)) + score(string(now, j, -1));
				if (mx < t) mx = t, id = j;
			}
			ret += mx; now = string(now, 0, id) + S[i] + string(now, id, -1);
		}
		return ret;
	}
};

/*
	Greed is good.
		- gold += 500
*/
