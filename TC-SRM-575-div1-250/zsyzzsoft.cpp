#include <algorithm>
using namespace std;
class TheNumberGameDivOne
{
public:
	string find(long long n)
	{
		if(n & 1)
			return "Brus";
		while(n % 4 == 0)
			n /= 4;
		return n == 2 ? "Brus" : "John";
	}
};