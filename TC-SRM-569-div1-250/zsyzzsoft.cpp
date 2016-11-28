#include <algorithm>
using namespace std;
class TheDevice
{
public:
	int minimumAdditional(vector<string> plates)
	{
		int cnt[51][2] = {0};
		for(int i = 0; i < plates.size(); i++)
		{
			for(int j = 0; j < plates[i].length(); j++)
				cnt[j][plates[i][j] == '1']++;
		}
		int ans = 0;
		for(int i = 0; cnt[i][0] + cnt[i][1]; i++)
			ans = max(ans, max(1 - cnt[i][0], 0) + max(2 - cnt[i][1], 0)); //需要一个0和两个1 
		return ans;
	}
};
