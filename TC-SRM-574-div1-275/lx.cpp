#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

class TheNumberGame
{
public : 
	string determineOutcome(int A, int B)
	{
		string a = to_string(A);
		string b = to_string(B);
		bool ans = a.find(b) != string::npos;
		reverse(b.begin(), b.end());
		ans |= a.find(b) != string::npos;
		return ans ? "Manao wins" : "Manao loses";
	}
};
