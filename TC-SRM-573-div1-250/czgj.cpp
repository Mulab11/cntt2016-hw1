/*
	Greedy, implementation.
*/

#include <bits/stdc++.h>
using namespace std;

class TeamContest {
	public:
	int worstRank(vector <int> s) {
		int str0 = max(max(s[0], s[1]), s[2]) + min(min(s[0], s[1]), s[2]); // Strength of the given team
		int n = s.size() / 3 - 1, ret = 1;
		multiset<int> S(s.begin() + 3, s.end()); // sort the other contestants in increasing order
		for (int i = 0; i < n; ++i){ // for each team
			int m1 = *S.begin(); S.erase(S.begin()); S.erase(S.begin()); // get two weakeast contestants
			multiset<int>::iterator it = S.upper_bound(str0 - m1); // find a BIG BROTHER
			if (it == S.end()) S.erase(S.begin()); // if the BIG BROTHER is not big enough, go die
				else S.erase(it), ++ret; // else carried by the BIG BROTHER and win!
		}
		return ret;
	}
};

/*
	I'm so happy~~~
	When I found you~~~~~~
	I'm so happy~~~~~
	When I~~~~ found you~~~~~
		- I'm so happy
*/
