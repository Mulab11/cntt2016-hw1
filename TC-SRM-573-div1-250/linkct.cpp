#include <bits/stdc++.h>
using namespace std;

class TeamContest{
public:
	map <int, int> sc;
	void remove(int x){
		if(!(-- sc[x])) sc.erase(x);
	}
	int worstRank(vector <int> score){
		int i, my = max(score[0], max(score[1], score[2])) + min(score[0], min(score[1], score[2])), n = score.size(), ans, cur;
		for(i = 3; i < n; ++ i)
			++ sc[score[i]];
		map <int, int> :: iterator it;
		for(ans = 1; !sc.empty(); ++ ans){
			-- (it = sc.end());
			remove(cur = it -> first);
			it = sc.upper_bound(my - cur);
			if(it == sc.end()) break;
			remove(it -> first);
			it = sc.upper_bound(my - cur);
			if(it == sc.end()) break;
			remove(it -> first);
		} return ans;
	}
};
