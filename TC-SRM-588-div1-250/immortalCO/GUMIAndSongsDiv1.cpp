#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

pair<int, int> p[60];

class GUMIAndSongsDiv1
{
public:
	int maxSongs(vector<int> a, vector<int> b, int lim)
	{
		// 枚举最小和最大的 tone 然后暴力
		int n = a.size();
		for(int i = 0; i != n; ++i) p[i] = make_pair(b[i], a[i]);
		sort(p, p + n);
		int ans = 0;
		for(int l = 0; l != n; ++l) for(int r = l; r != n; ++r)
		{
			vector<int> vec;
			for(int i = l; i <= r; ++i) vec.push_back(p[i].second);
			sort(vec.begin(), vec.end());
			int i = 0, s = p[r].first - p[l].first;
			while(i != r - l + 1 && (s += vec[i]) <= lim) ++i;
			if(i > ans) ans = i;
		}
		return ans;
	}
}   user;
