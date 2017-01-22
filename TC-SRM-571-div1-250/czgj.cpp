/*
	Greedy, implementation.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class FoxAndMp3 {
	public:
	string str(LL n){ // Convert a number to a string.
		string ret;
		while (n) ret += '0' + n % 10, n /= 10;
		reverse(ret.begin(), ret.end());
		return ret;
	}
	LL next(LL v, LL n){
		if (v * 10 <= n) return v * 10; // Add a zero (if it is still not greater than n)
		else {
			while (v >= n) v = v / 10; ++v;// Find a bit and add one.
			while(v % 10 == 0) v /= 10; // Throw 0 away
			return v;
		}
	}
	vector <string> playList(int n) {
		vector<string> ret;
		LL v = 1; 
		for (int i = 1; i <= n && i <= 50; ++i){
			ret.push_back(str(v) + ".mp3");
			v = next(v, n);
		}
		return ret;
	}
};

/*
	Kyou wa kaze ga
	sawagashii na
	Demo sugoshi kono kaze
	naiteimasu
		- Danshi Koukousei no Nichijou
*/
