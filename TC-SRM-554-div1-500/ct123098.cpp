#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

vector<int> h;
bool cmp(int x, int y)
{
	if(h[x] != h[y])
		return h[x] < h[y];
	return x < y;
}

class TheBrickTowerMediumDivOne
{
	public:
	int n;
	vector<int> a, b, ans;

	vector<int> find(vector<int> heights)
	{
		h = heights;
		n = heights.size();

		for(int i = 0; i < n; i++)
		{
			if(!a.size() || h[a[a.size() - 1]] >= h[i])
				a.push_back(i);
			else
				b.push_back(i);
		}
		sort(b.begin(), b.end(), cmp);
		
		for(int i = 0; i < a.size(); i++)
			ans.push_back(a[i]);
		for(int i = 0; i < b.size(); i++)
			ans.push_back(b[i]);

		return ans;
	}
};

