/*
	Brute force & greedy.
*/

#include <bits/stdc++.h>
using namespace std;
class BallsSeparating {
	public:
	int minOperations(vector <int> red, vector <int> green, vector <int> blue) {
		int n = red.size(), ret = 666666666;
		vector<int> sum; sum.resize(n);
		for (int i = 0; i < n; ++i) sum[i] = red[i] + green[i] + blue[i]; // Preprocess sum
		if (n < 3) return -1; // That's impossible
		for (int i = 0; i < n; ++i) // Assign a box to red
			for (int j = 0; j < n; ++j) if (i != j) // Assign a box to green
				for (int k = 0; k < n; ++k) if (i != k && j != k){ // Assign a box to blue
					int t = sum[i] + sum[j] + sum[k] - red[i] - green[j] - blue[k]; // Cost for the three boxes
					for (int l = 0; l < n; ++l) if (i != l && j != l && k != l) // Assign other boxes greedily
						t += sum[l] - max(red[l], max(green[l], blue[l])); // Add the cost
					if (ret > t) ret = t; // Update answer
				}
		return ret;
	}
};

/*
	Onegai kiss de
	me wo samashite hoshii no
		- Shiroi Yuki no Princess wa
*/

