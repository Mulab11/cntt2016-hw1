/*
	Brute force & Greedy.
	Go over all the ways to assign sizes to problems.
	Then greedily assign more bloons to more AC problems and do the repaintings.
*/
#include <bits/stdc++.h>
using namespace std;
const int INF = 23333;
class ICPCBalloons {
	public:
	int calc(vector<int> bloon, vector<int> maxAC){
		int n = maxAC.size(), nb = bloon.size(), sumb = 0, sumac = 0, ret = 0;
		for (int i = 0; i < nb; ++i) sumb += bloon[i];
		for (int i = 0; i < n; ++i) sumac += maxAC[i];
		if (sumb < sumac) return INF; // Not enough bloons (in total)
		for (int i = 0; i < n; ++i) ret += max(0, maxAC[i] - bloon[i]);
		return ret;
	}
	int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted) {
		int bloonC = balloonCount.size(), n = maxAccepted.size(), ret = INF * 10;
		vector<int> bloon[2], prob[2];
		int mask = (1 << n) - 1;
		for (int i = 0; i < bloonC; ++i) bloon[balloonSize[i] == 'M'].push_back(balloonCount[i]); // Push bloons to correct vectors.
		for (int i = 0; i <= 1; ++i){
			sort(bloon[i].begin(), bloon[i].end(), greater<int>());
			while (bloon[i].size() <= n) bloon[i].push_back(0); // Push enough elements.
		}
		sort(maxAccepted.begin(), maxAccepted.end(), greater<int>());
		for (int i = 0; i <= mask; ++i){ // Go over all ways to divide the problems.
			prob[0].clear(); prob[1].clear();
			for (int j = 0; j < n; ++j)
				prob[i >> j & 1].push_back(maxAccepted[j]);
			int t = calc(bloon[0], prob[0]) + calc(bloon[1], prob[1]);
			if (t < ret) ret = t;
		}
		return ret < INF ? ret : -1;
	}
};

/*
	My Little Pony,
	I used to wonder what friendship could be.
	My Little Pony,
	Until you all shared its magic with me.
		- Rainbow Dash Likes Girls
*/

