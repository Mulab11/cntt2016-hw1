#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

class TeamContest
{
public:
	int worstRank(vector<int> vec)
	{
		const int cur = min(min(vec[0], vec[1]), vec[2]) + max(max(vec[0], vec[1]), vec[2]);
		int l = 3, r = vec.size() - 1, ans = 0, found = 0;
		sort(vec.data() + l, vec.data() + r + 1);
		while(l < r)
		{
			while(l + 1 < r && vec[l] + vec[r] <= cur) ++l, ++found;
			if(found > ans) found = ans;
			if(l + 1 == r) break;
			if(ans >= found + r - l - 1) break;
			++ans, ++l, --r;
		}
		return ans + 1;
	}
}   user;
