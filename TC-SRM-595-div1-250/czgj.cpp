/*
	Find out the number of stages that make effects on the final results,
	that is : cannot be completely covered by the stages after them.
*/

#include <bits/stdc++.h>
using namespace std;

class LittleElephantAndIntervalsDiv1 {
	public:
	long long getNumber(int M, vector <int> L, vector <int> R) {
		bool mark[2333]; memset(mark, 0, sizeof mark);
		int n = L.size(), ret = 0;
		for (int i = n - 1; i >= 0; --i){
			bool ok = 0;
			for (int j = L[i]; j <= R[i]; ++j){
				if (!mark[j]) ok = 1; // not covered after
				mark[j] = 1;
			}
			ret += ok;
		}
		return 1ll << ret;
	}
};

/*
	Laeeeeevatein
		- Taboo tears you up
*/
