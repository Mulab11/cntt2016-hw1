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

class TheBrickTowerEasyDivOne
{
	public:
	int find(int redCount, int redHeight, int blueCount, int blueHeight)
	{
		if(redHeight == blueHeight)
		{
			if(redCount == blueCount)
				return 2 * redCount;
			else
				return 2 * min(redCount, blueCount) + 1;
		}
		else
		{
			if(redCount == blueCount)
				return 3 * redCount;
			else
				return 3 * min(redCount, blueCount) + 1;
		}
		
		
		return 0;
	}
};

