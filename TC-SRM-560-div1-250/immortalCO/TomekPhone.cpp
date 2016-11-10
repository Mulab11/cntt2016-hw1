#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

class TomekPhone
{
public:
	int minKeystrokes(vector<int> cnt, vector<int> lim)
	{
		vector<int> use(lim.size(), 0);
		std::sort(cnt.begin(), cnt.end());
		reverse(cnt.begin(), cnt.end());
		int ans = 0;
		for(int i = 0; i != (int) cnt.size(); ++i)
		{
			int p = -1, v = 100000;
			for(int k = 0; k != (int) lim.size(); ++k)
				if(use[k] != lim[k] && v > use[k])
					v = use[p = k];
			if(p == -1) return -1;
			ans += cnt[i] * ++use[p];
		}
		return ans;
	}
}	user;
