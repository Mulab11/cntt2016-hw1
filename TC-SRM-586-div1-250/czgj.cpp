/*
	Discretize the y coordinates,
	Do the counting with difference array.
*/

#include <bits/stdc++.h>
using namespace std;

class PiecewiseLinearFunction {
	public:
	int maximumSolutions(vector <int> Y) {
		int n = Y.size(), vn, a[233]; memset(a, 0, sizeof a);
		// Spj
		for (int i = 1; i < n; ++i) if (Y[i] == Y[i - 1]) return -1; 
		// Discretize
		vector<int> val = Y; sort(val.begin(), val.end());
		vn = unique(val.begin(), val.end()) - val.begin(); val.resize(vn); 
		for (int i = 0; i < n; ++i) Y[i] = lower_bound(val.begin(), val.end(), Y[i]) - val.begin() + 1;
		// Counting
		++a[Y[0] * 2]; --a[Y[0] * 2 + 1]; // spj the first point
		for (int i = 1; i < n; ++i){
			int l = Y[i - 1] * 2 + (Y[i] > Y[i - 1] ? 1 : -1), r = Y[i] * 2; 
			if (l > r) swap(l, r);
			a[l] += 1, a[r + 1] -= 1;
		}
		// Find the answer
		int ans = 0;
		for (int i = 1; i <= vn * 2 + 1; ++i)
			ans = max(ans, a[i] += a[i - 1]);
		return ans;
	}
};

/*
	Gurarinri kimi ni kikoeru nowa
	Boku ga shiranai koe ni natteku
		- No Title
*/

