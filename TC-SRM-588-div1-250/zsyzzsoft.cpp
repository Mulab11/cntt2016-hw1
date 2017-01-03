#include <algorithm>
using namespace std;
class GUMIAndSongsDiv1
{
public:
	int maxSongs(vector<int> d, vector<int> x, int t)
	{
		int n = d.size();
		pair<int, int> a[50];
		for(int i = 0; i < n; i++)
			a[i] = make_pair(d[i], x[i]);
		sort(a, a + n);
		int ans = 0;
		for(int i = 0; i < n; i++) //枚举最小音调与最大音调 
		{
			for(int j = 0; j < n; j++)
			{
				int l = a[i].second, r = a[j].second;
				if(l > r)
					continue;
				int cnt = 0;
				for(int k = 0, rest = t - (r - l); k < n; k++) //贪心在范围内选择时间短的 
				{
					if(a[k].second >= l && a[k].second <= r && rest >= a[k].first)
						rest -= a[k].first, cnt++;
				}
				ans = max(ans, cnt);
			}
		}
		return ans;
	}
};