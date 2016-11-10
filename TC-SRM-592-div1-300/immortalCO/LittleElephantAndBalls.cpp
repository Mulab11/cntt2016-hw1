#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

class LittleElephantAndBalls
{
public:
	int getNumber(string s)
	{
		int ans = 0, cnt[256] = {};
		for(int i = 0; i != (int) s.size(); ++i)
		{
			ans += min(cnt['R'], 2) + min(cnt['G'], 2) + min(cnt['B'], 2);
			++cnt[s[i]];
		}
		return ans;
	}
}   user;
