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

const int MAXN = 50 + 10;

class CheckerExpansion
{
	public:
	
	vector<string> map;
	
	char getChar(long long t, long long x, long long y)
	{
		if((x + y) % 2 == 1)
			return '.';
		long long n = (x + y) / 2, m = y;
		if(t <= n)
			return '.';
		if((~n) & m)
			return '.';
		return n & 1 ? 'B' : 'A';
	}
	
	vector<string> resultAfter(long long t, long long x0, long long y0, int w, int h)
	{
		map.resize(h);
		for(int i = 0; i < h; i++)
		{
			map[i].resize(w);
			for(int j = 0; j < w; j++)
				map[i][j] = getChar(t, x0 + j, y0 + h - i - 1);
		}
		return map;
	}
};

