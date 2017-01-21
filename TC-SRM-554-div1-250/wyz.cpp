// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBrickTowerEasyDivOne.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

class TheBrickTowerEasyDivOne {
	public:
	int find(int redCount, int redHeight, int blueCount, int blueHeight){
		return min(redCount,blueCount)*(2+(redHeight!=blueHeight))+(redCount!=blueCount);
	}
};
