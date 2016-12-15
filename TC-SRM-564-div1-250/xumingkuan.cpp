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
class KnightCircuit2
{
	public:
	int maxSize(int w, int h)
	{
		if(w > h)//make w <= h.
			swap(w, h);
		if(w == 1)
			return 1;
		/*w == 2:
		1...3...5...7..
		..2...4...6...8
		*/
		if(w == 2)
			return (h + 1) / 2;
		if(w == 3 && h == 3)
			return 8;//can't visit the center of the board
		return w * h;
	}
};

