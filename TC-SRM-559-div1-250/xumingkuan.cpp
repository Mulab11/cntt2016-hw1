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

class HyperKnight
{
	/*
	23444432
	34666643
	46888864
	46888864
	46888864
	46888864
	34666643
	23444432*/
	public:
	long long countCells(int a, int b, int numRows, int numColumns, int k)
	{
		if(a > b)
			swap(a, b);
		//if(numRows > numColumns)
		//	swap(numRows, numColumns);
		switch(k)
		{
			case 8:
				return (long long)(numRows - b * 2) * (numColumns - b * 2);
			case 6:
				return 2 * (long long)(b - a) * ((long long)numColumns - b * 2 + numRows - b * 2);
			case 4:
				return 2 * a * ((long long)numColumns - b * 2 + numRows - b * 2) + 4 * (long long)(b - a) * (b - a);
			case 3:
				return (long long)a * (b - a) * 8;
			case 2:
				return (long long)a * a * 4;
			default:
				return 0;
		}
		return 0;
	}
};

