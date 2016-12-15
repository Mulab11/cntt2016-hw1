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

class SpellCards
{
	private:
	int n, f[60];//f[i]: max damage using i cards
	public:
	int maxDamage(vector<int> level, vector<int> damage)//the order of the cards doesn't matter. it's just a "01-beibao".
	{
		memset(f, 0, sizeof(f));
		n = level.size();
		for(int i = 0; i < n; i++)
			for(int j = n; j >= level[i]; j--)
				f[j] = max(f[j - level[i]] + damage[i], f[j]);
		return f[n];
	}
};

