#include <algorithm>
using namespace std;
class LittleElephantAndBalls
{
public:
	int getNumber(string s)
	{
		int ans = 0;
		for(int i = 0, r = 0, g = 0, b = 0; i < s.length(); i++)
		{
			ans += min(r, 2) + min(g, 2) + min(b, 2); //一定可以把前面出现过两次的颜色都分在两侧 
			if(s[i] == 'R')
				r++;
			else if(s[i] == 'G')
				g++;
			else
				b++;
		}
		return ans;
	}
};