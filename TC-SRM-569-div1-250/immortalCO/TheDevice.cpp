#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

class TheDevice
{
public:
	int minimumAdditional(vector<string> vec)
	{
		int ans = 0;
		for(int d = 0; d != (int) vec[0].size(); ++d)
		{
			int cnt[2] = {};
			for(int i = 0; i != (int) vec.size(); ++i)
				++cnt[vec[i][d] == '1'];
			ans = max(ans, max(0, 1 - cnt[0]) + max(0, 2 - cnt[1]));
		}
		return ans;
	}
}	user;
