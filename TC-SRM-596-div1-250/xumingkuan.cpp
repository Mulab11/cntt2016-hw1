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

class IncrementAndDoubling
{
public:
	int getMin(vector<int> desiredArray)
	{
		int minclz = 31, totcnt = 0;
		for(vector<int>::iterator it = desiredArray.begin(); it != desiredArray.end(); it++)
		{
			totcnt += __builtin_popcount(*it);
			if(*it)
				minclz = min(minclz, __builtin_clz(*it));
		}
		return totcnt + 31 - minclz;
	}
};

