/*
	go down down down then up up up.
	do some greed to get the lexi. smallest order.
*/

#include <bits/stdc++.h>
using namespace std;

class TheBrickTowerMediumDivOne {
	public:
	vector <int> find(vector <int> heights) {
		vector<int> ret;
		vector<pair<int, int> > a;
		int t = 233;
		for (int i = 0; i < heights.size(); ++i)
			if (heights[i] <= t) t = heights[i], ret.push_back(i);
				else a.push_back(pair<int, int>(heights[i], i));
		sort(a.begin(), a.end());
		for (int i = 0; i < a.size(); ++i)
			ret.push_back(a[i].second);
		return ret;
	}
};

/*
	El Psy Congroo.
		- Hououin Kyouma(Okabe Rintarou)
*/
