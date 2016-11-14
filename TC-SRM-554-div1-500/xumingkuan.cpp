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
#include <cctype>
#include <queue>
#include <map>
using namespace std;

class TheBrickTowerMediumDivOne
{
	private:
	bool used[60];
	public:
	vector<int> find(vector<int> heights)
	{
		const int n = heights.size();
		vector <int> ret(1, 0);//place the first tower.
		memset(used, false, sizeof(used));
		used[0] = true;
		bool ok = true;
		while(ok && ret.size() < n)
		{
			ok = false;
			for(int j = 0; j < n; j++)
				if(!used[j] && heights[j] <= heights[ret.back()])//greedy. select lexicographically smallest lower tower.
				{
					ret.push_back(j);
					used[j] = ok = true;
					break;
				}
		}
		//reach the lowest tower.
		while(ret.size() < n)//selection sort.
		{
			int minHeight = 1010101010, place = -1;
			for(int j = 0; j < n; j++)
				if(!used[j] && heights[j] < minHeight)
					minHeight = heights[j], place = j;
			ret.push_back(place);
			used[place] = true;
		}
		return ret;
	}
};

