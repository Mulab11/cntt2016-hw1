#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TheTree
{
public:
	int maximumDiameter(vector<int> cnt)
	{
		int ans = cnt.size(), last = 0;//height of last '1' in 'cnt'
		for(int i = 1; i <= cnt.size(); i++)
		{
			if(cnt[i - 1] == 1)
				last = i;
			ans = max(ans, (int)cnt.size() + i - last * 2);//height of lca is 'last'
		}
		return ans;
	}
};

