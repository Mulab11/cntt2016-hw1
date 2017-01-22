/*
	Greedy.
	Just consider what to do with only 1 number.
	Answer = \sum popcount(a_i) + \max log2(a_i)
*/ 

#include <bits/stdc++.h>
using namespace std;

class IncrementAndDoubling {
	public:
	int getMin(vector <int> desiredArray) {
		int sum = 0, mxl = 0, n = desiredArray.size();
		for (int i = 0; i < n; ++i){
			int t = desiredArray[i];
			sum += __builtin_popcount(t);
			mxl = max(mxl, (int)(log(t + 1e-6) / log(2)));
		}
		return sum + mxl;
	}
};

/*
	Tameru nara, rarara rakuten pointo~~~
	Tsukau nara, rarara rakuten pointo~~~
	Tamaru, Tsukaeru, RAKUTEN POINT! 
*/
