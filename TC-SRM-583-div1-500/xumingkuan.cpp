#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class TurnOnLamps
{
private:
	int n;
	int f[55];//f[u]: number of paths need to be toggled from u to some point in subtree u
public:
	int minimize(vector<int> roads, string initState, string isImportant)
	{
		n = roads.size() + 1;
		memset(f, 0, sizeof(f));
		int ans = 0;
		for(int i = n - 1; i >= 1; i--)
		{
			ans += f[i] / 2;
			int now = f[i] % 2;
			if(isImportant[i - 1] == '1')
			{
				if(initState[i - 1] == '1')//we shouldn't toggle road i-1; if f[i] is odd, we should toggle the remaining path from i.
				{
					ans += now;
					now = 0;
				}
				else//we must toggle road i-1
					now = 1;
			}
			f[roads[i - 1]] += now;
		}
		ans += (f[0] + 1) / 2;//point 0 doesn't have a father
		return ans;
	}
};

