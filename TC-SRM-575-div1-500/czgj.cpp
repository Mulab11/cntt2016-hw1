/*
	Expected Value
	Math
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class TheSwapsDivOne {
	public:
	double find(vector <string> sequence, int k) {
		// p0 = prob that i stays at i after k moves
		double p0 = 1, ret = 0; string st; int n, sum = 0;
		rep(i, 0, (int)sequence.size() - 1) st += sequence[i];
		n = st.length(); rep(i, 0, n - 1) sum += st[i] -= '0';
		p0 = pow((double)(n - 3) / (n - 1), k) * (n - 1) / n + 1.0 / n; // some magic formula
		rep(i, 0, n - 1){ // for each position
			double prob = (double)(i + 1) * (n - i) / (n * (n + 1) / 2);
			double val = st[i] * p0 + (sum - st[i]) * (1 - p0) / (n - 1);
			ret += prob * val;
		}
		return ret;
	}
};

/*
	Anata wa
	Shinji rare masuka?
*/

