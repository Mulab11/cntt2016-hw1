#include <bits/stdc++.h>
using namespace std;

class TheNumberGame{
public:
	string determineOutcome(int A, int B){
		stringstream c1, c2; string a, b;
		c1 << A; c1 >> a;
		c2 << B; c2 >> b;
		if(a.find(b) != a.npos) return "Manao wins";
		reverse(b.begin(), b.end());
		return a.find(b) != a.npos ? "Manao wins" : "Manao loses";
	}
};
