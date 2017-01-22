/*
	Some features of the diameter of a tree.
	There must be a node of depth D on the diameter.
	So for every depth i find another longest path. 
*/

#include <bits/stdc++.h>
using namespace std;

class TheTree {
	public:
	int maximumDiameter(vector <int> cnt) {
		int f[64], n = cnt.size(), ret = 0; memset(f, 0, sizeof f);
		for (int i = n - 1; i >= 0; --i) ret = max(ret, n - i + (f[i] = cnt[i] > 1 ? 1 + f[i + 1] : 0));
		return ret;
	}
};

/*
	I'm turning my head up and down.
	I'm turning, turning, turning, turning, turning around.
	And all that I can see is just another lemon tree.
		- Lemon tree
*/
