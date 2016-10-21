#include <algorithm>
using namespace std;
class FoxAndMountainEasy
{
public:
	string possible(int n, int a, int b, string history)
	{
		for(int i = 0; i < history.length(); i++)
			history[i] == 'U' ? a++ : a--;
		n -= history.length();
		return abs(a - b) <= n && (a + n - b) % 2 == 0 ? "YES" : "NO";
	}
};