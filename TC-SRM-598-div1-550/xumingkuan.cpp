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

class FoxAndFencing
{
public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
	{
		string name1 = "Ciel", name2 = "Liss", draw = "Draw";
		if(mov1 + rng1 >= d)//first turn
			return name1;
		if(mov2 + rng2 >= d + mov1)//second turn
			return name2;
		if(mov1 == mov2)
			return draw;
		if(mov1 < mov2)//name1 is active
			swap(mov1, mov2), swap(rng1, rng2), swap(name1, name2);
		if(rng2 + mov2 * 2 < rng1 + mov1)
			return name1;
		return draw;
	}
};

