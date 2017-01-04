#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class TeamContest
{
public:
	int worstRank(vector<int> strength)
	{
		int myTeam = min(strength[0], min(strength[1], strength[2])) + max(strength[0], max(strength[1], strength[2]));
		sort(strength.begin() + 3, strength.end());
		int ptr = 3, ans = 1;
		for(int i = strength.size() - 1; i > ptr + 1; i--)//greedy, two pointers
		{
			while(strength[i] + strength[ptr] <= myTeam && i > ptr + 1)
				ptr++;
			if(i <= ptr + 1)//no enough students
				break;
			ans++, ptr += 2;//new Team(i, ptr, ptr + 1);
		}
		return ans;
	}
};

