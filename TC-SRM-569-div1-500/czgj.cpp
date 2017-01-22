/*
	Greedy.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class TheJediTest {
	public:
	int minimumSupervisors(vector <int> a, int K) {
		vector<int> b(a); int n = a.size(), ret = 0;
		rep(i, 0, n - 1){
			if (i == n - 1 && b[i]) ret += (b[i] - 1) / K + 1;
			else if (b[i] % K <= a[i]){ // up
				ret += b[i] / K;
				b[i + 1] += b[i] % K;
			}
			else { // down
				ret += b[i] / K + 1;
				b[i + 1] -= min(b[i + 1], K - b[i] % K);
			}
		}
		return ret;
	}
};

/*
	Konya saikou.
*/
