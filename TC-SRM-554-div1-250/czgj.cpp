/*
	Easy math.
	No comment.
*/

#include <bits/stdc++.h>
using namespace std;

class TheBrickTowerEasyDivOne {
	public:
	int find(int redCount, int redHeight, int blueCount, int blueHeight) {
		if (redCount > blueCount) swap(redCount, blueCount);
		return redCount * ((redHeight != blueHeight) + 2) + (redCount != blueCount);
	}
};

/*
	Ipponmanzoku!
		- Ipponmanzoku bar
*/
