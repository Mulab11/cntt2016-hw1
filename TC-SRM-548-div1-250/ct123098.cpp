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

const int MAXN = 100 + 10;

class KingdomAndTrees
{
	public:
	
	int n, a[MAXN];
	
	bool check(int k)
	{
		int cur = 0;
		for(int i = 1; i <= n; i++)
		{
			int lower = a[i] - k, upper = a[i] + k;
			cur = max(cur + 1, lower);
			if(cur > upper)
				return false;
		}
		return true;
	}
	
	int binary(int l, int r)
	{
		while(l < r)
		{
			int mid = (l + r) / 2;
			if(check(mid)) // [l, mid]
				r = mid;
			else // [mid + 1, r]
				l = mid + 1;			
		}
		return l;
	}
	
	int minLevel(vector<int> heights)
	{
		n = heights.size();
		for(int i = 1; i <= n; i++)
			a[i] = heights[i - 1];
		int ans = binary(0, 1000000000 + 1000);
		
		return ans;
	}
};

