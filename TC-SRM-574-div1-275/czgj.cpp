/*
	Manao wins only when B is a substring of A or reversed A.
	Very obvious, isn't it?
*/

#include <bits/stdc++.h>
using namespace std;

class TheNumberGame {
	public:
	const int pow10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	bool check(int A, int B){
		for (int i = 0; i < 9; ++i) for (int j = i; j <= 9; ++j) if (A % pow10[j] / pow10[i] == B) return 1;
		return 0;
	}
	int reversed(int A){
		int ret = 0;
		while (A) ret = ret * 10 + A % 10, A /= 10;
		return ret;
	}
	string determineOutcome(int A, int B) {
		return check(A, B) || check(reversed(A), B) ? "Manao wins" : "Manao loses";
	}
};

/*
	Nagareboshi sae matenai noyo
	Konya dake wa kanaete yo
		- Koigokoro
*/
