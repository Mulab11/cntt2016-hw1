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

class KingdomAndTrees
{
private:
	int n, h[55];
	bool check(int x)
	{
		int last = max(1, h[0] - x);
		for(int i = 1; i < n; i++)
		{
			if(h[i] + x <= last)
				return false;
			last = max(last + 1, h[i] - x);//greedy
		}
		return true;
	}
public:
	int minLevel(vector<int> heights)
	{
		n = heights.size();
		for(int i = 0; i < n; i++)
			h[i] = heights[i];
		int l = 0, r = 1010101010;//er fen da an
		while(l < r)
		{
			int m = (l + r) >> 1;
			if(check(m))
				r = m;
			else
				l = m + 1;
		}
		return l;
	}
};

