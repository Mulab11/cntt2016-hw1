/*
	Greedy.
	Allocate less keystrokes to frequent alphabets.
*/
#include <bits/stdc++.h>
using namespace std;
class TomekPhone {
	public:
	int minKeystrokes(vector <int> frequencies, vector <int> keySizes) {
		int n = frequencies.size(), ret = 0;
		vector<int> s;
		for (int i = 0; i < keySizes.size(); ++i) // Push all the keystrokes
			for (int j = 1; j <= keySizes[i]; ++j)
				s.push_back(j);
		if (s.size() < n) return -1; // not enough, return -1
		sort(s.begin(), s.end()); sort(frequencies.begin(), frequencies.end(), greater<int>());
		for (int i = 0; i < n; ++i) ret += frequencies[i] * s[i]; // get the answer
		return ret;
	}
};

/*
	Konomama Tobi Tateba
	Dokoni datte yukeru...
		- Megumeru
*/
