// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorAndSum.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

struct XorAndSum {
    long long maxSum(vector<long long> number) {
		ll ans = 0;
		// greedy algorithm
		for(int i = 0; i < SZ(number); ++i) {
			static ll base[60];
			memset(base, 0, sizeof base);
			// generate linear base of other numbers
			for(int j = 0; j < SZ(number); ++j)
				if(i != j) {
					for(int k = 59; k >= 0; --k)
						if(number[j] >> k & 1) {
							if(!base[k]) {
								base[k] = number[j];
								break;
							}
							else number[j] ^= base[k];
						}
				}
			// use other numbers to make number[i] maximal
			for(int j = 59; j >= 0; --j)
				if(!(number[i] >> j & 1)) number[i] ^= base[j];
			ans += number[i];
		}
		return ans;
    }
};
