/*
	Easy math.
	No comment.
*/

#include <bits/stdc++.h>
using namespace std;

class FoxAndMountainEasy {
	public:
	string possible(int n, int h0, int hn, string history) {
		if (((hn - h0) & 1) ^ (n & 1)) return "NO";
		int dh = 0, mindh = 0, len = history.length();
		for (int i = 0; i < len; ++i)
			mindh = min(mindh, dh += history[i] == 'U' ? 1 : -1);
		int mint = max(-mindh - h0, 0);
		return abs(hn - (h0 + mint + dh)) > n - len - mint ? "NO" : "YES";
	}
};

/*
	What does the fox say?
	Ring-ding-ding-ding-dingeringeding
		- What does the fox say
*/
