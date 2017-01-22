/*
	Every bin only contains 1~3 items.
	Greedy.
*/

#include <bits/stdc++.h>
using namespace std;

class BinPacking {
	public:
	int minBins(vector <int> item) {
		multiset<int> S(item.begin(), item.end());
		int ret = 0;
		while (!S.empty()){
			multiset<int, greater<int> >::iterator it = S.end(); --it; // find the biggest one
			int w = *it; S.erase(it); ++ret; // put the biggest one into a bin
			while ((it = S.upper_bound(300 - w)) != S.begin()) // as long as the bin still fits
				w += *--it, S.erase(it); // put it into the bin
		}
		return ret;
	}
};

/*
	Uketomete
	Shinde wwww
		- Oyome ni Shinasai
*/
