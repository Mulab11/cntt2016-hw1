#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

#include <sstream>

class TheNumberGame
{
public:
	string determineOutcome(int x, int y)
	{
		stringstream aa, bb;
		aa << x; string a = aa.str();
		bb << y; string b = bb.str();
		if(a.find(b) != -1) return "Manao wins";
		reverse(a.begin(), a.end());
		if(a.find(b) != -1) return "Manao wins";
		return "Manao loses";
	}
}	user;
