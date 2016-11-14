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

using namespace std;

class CheckerExpansion
{
	private:
	char getResult(long long t, long long x, long long y)
	{
		long long n = ((x + y) >> 1), p = ((x - y) >> 1);//turn, place
		if(((x + y) & 1) || n >= t || x < y)//not a turn || >t turn || out of grid
			return '.';
		const char res = (n & 1) + 'A';//player
		for(int i = 40; i >= 0; i--)
			if(n & (1ll << i))
			{
				n ^= (1ll << i);
				if(p & (1ll << i))
					p ^= (1ll << i);
				if(p > n)//empty
					return '.';
			}
		return res;
	}
	public:
	vector<string> resultAfter(long long t, long long x0, long long y0, int w, int h)
	{
		vector <string> ret;
		for(int i = 0; i < h; i++)
		{
			string now;
			for(int j = 0; j < w; j++)
				now += getResult(t, x0 + j, y0 + h - i - 1);
			ret.push_back(now);
		}
		return ret;
	}
};

