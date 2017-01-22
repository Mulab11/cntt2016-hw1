/*
	Implementation.
*/

#include <bits/stdc++.h>
using namespace std;

class FoxAndChess {
	public:
	string ableToMove(string begin, string target) {
		int n = begin.length(), sum0 = 0, sum1 = 0;
		string s1, s2;
		for (int i = 0; i < n; ++i){
			if (begin[i] != '.'){
				s1 += begin[i];
				++(begin[i] == 'L' ? sum0 : sum1);
			}
			if (target[i] != '.'){
				s2 += target[i];
				--(target[i] == 'L' ? sum0 : sum1);
			}
			if (sum0 > 0 || sum1 < 0) return "Impossible"; // Check invalid L / R moves
		}
		return s1 != s2 ? "Impossible" : "Possible"; // Check relative positions
	}
};

/*
	glgjssy
	qyhfbqz
	+1s
*/
