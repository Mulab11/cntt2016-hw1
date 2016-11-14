#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

class PointyWizardHats
{
	private:
	int n, m;
	pair <int, int> a[60], b[60];
	bool used[60];
	public:
	int getNumHats(vector<int> topHeight, vector<int> topRadius, vector<int> bottomHeight, vector<int> bottomRadius)
	{
		n = topHeight.size();
		m = bottomHeight.size();
		for(int i = 0; i < n; i++)
			a[i] = make_pair(topRadius[i], -topHeight[i]);
		for(int i = 0; i < m; i++)
			b[i] = make_pair(bottomRadius[i], bottomHeight[i]);
		sort(a, a + n);
		sort(b, b + m);
		memset(used, false, sizeof(used));
		int ans = 0;
		for(int i = n - 1; i >= 0; i--)//top: radius ascend, then height descend
		{
			int now = -1;
			double val = 0;
			for(int j = m - 1; j >= 0 && b[j].first > a[i].first; j--)//bottom: radius > top's
				if(!used[j] && b[j].second * a[i].first / (double)b[j].first + 1e-8 < -a[i].second && b[j].second * a[i].first / (double)b[j].first > val)
					now = j, val = b[j].second * a[i].first / (double)b[j].first;//find nearest bottom (radius / height) (< top's)
			if(now != -1)
			{
				used[now] = true;
				ans++;
			}
		}
        return ans;
	}
};
