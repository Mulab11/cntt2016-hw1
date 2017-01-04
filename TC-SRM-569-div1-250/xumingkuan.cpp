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
#include <queue>
using namespace std;
class TheDevice
{
	public:
	int minimumAdditional(vector<string> plates)
	{
		int ans = 0;
		for(int j = 0; j < plates[0].size(); j++)
		{
			int num[2] = {0, 0};
			for(int i = 0; i < plates.size(); i++)
				num[plates[i][j] - '0']++;
			ans = max(ans, (!num[0]) + max(2 - num[1], 0));
		}
		return ans;
	}
};

