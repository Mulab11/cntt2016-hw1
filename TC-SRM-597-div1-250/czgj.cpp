/*
	The unchanged characters of A make a suffix of B.
	The others can be rearranged in any order.
	So the answer = n - maxSuffixLength
*/

#include <bits/stdc++.h>
using namespace std;

class LittleElephantAndString {
	public:
	int getNumber(string A, string B) {
		string tA = A; sort(tA.begin(), tA.end());
		string tB = B; sort(tB.begin(), tB.end());
		if (tA != tB) return -1; // Different character set
		int cnt = 0, n = A.length();
		for (int i = n - 1; i >= 0; --i)
			if (A[i] == B[n - cnt - 1]) ++cnt;
		return n - cnt;
	}
};

/*
	THEYYYY WILLLLL REEEEE-TURNNNNNN
	AAAAAAAAAAAAAAAAA
		- Buki A
*/
