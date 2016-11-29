#include <algorithm>
using namespace std;
class FoxAndMountainEasy
{
public:
	string possible(int n, int a, int b, string history)
	{
		int h = 0;
		for(int i = 0; i < history.length(); i++, h = min(h, a))
			history[i] == 'U' ? a++ : a--;
		a -= h; //最小初始高度 
		n -= history.length() - h;
		return abs(a - b) <= n && (a + n - b) % 2 == 0 ? "YES" : "NO";
	}
};