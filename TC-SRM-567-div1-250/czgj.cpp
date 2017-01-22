/*
	Easy math.
	No comment.
*/

#include <bits/stdc++.h>
using namespace std;
class TheSquareRootDilemma {
	public:
	int countPairs(int N, int M) {
		int ans = 0;
		// a, b = k * (i ^ 2); i, k is square-free
		for (int i = 1; i <= N; ++i){
			bool ok = 1;
			for (int j = 2; j * j <= i; ++j) // Check if i is square-free
				if (i % (j * j) == 0) {ok = 0; break;}
			if (ok) ans += (int)sqrt(N / i) * (int)sqrt(M / i); // count it
		}
		return ans;
	}
};

/*
	SSR is GOD (hakushin
*/
