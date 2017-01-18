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

class FoxAndAvatar
{
public:
	int minimalSteps(int n, int width, int x, int lim = 4)//ans <= 4
	{
		//printf("search n=%d width=%d x=%d lim=%d\n", n, width, x, lim);
		if(n == 1 || lim == 0)
			return 0;
		if((x == 1 && (width == 1 || n <= width)) || (x == n && (width == 1 || n % width == 1 || n <= width)) || (x == width && n < width * 2) || lim == 1)
			return 1;
		if(lim == 2)
			return 2;
		int row = (x - 1) / width + 1, col = (x - 1) % width + 1, totrow = n / width, totcol = n % width;
		for(int i = 1; i < col; i++)//left
			for(int j = 0; j <= row; j++)
				if((lim = minimalSteps(n - ((totrow - j) * i + min(totcol, i)), width, x - (row - j) * i, lim - 1) + 1) == 2)
					return 2;
		for(int i = col + 1; i <= width; i++)//right
			for(int j = 0; j < row; j++)
				if((lim = minimalSteps(n - ((totrow - j) * (i - col) + max(min(totcol, i) - col, 0)), width, x - (row - j - 1) * (i - col), lim - 1) + 1) == 2)
					return 2;
		for(int i = max(col, width - col + 1); i <= width; i++)//up
			for(int j = 1; j < row; j++)
				if((lim = minimalSteps(n - i * j, width, x - i * j, lim - 1) + 1) == 2)
					return 2;
		return lim = minimalSteps(min(n, row * width), width, x, lim - 1) + 1;//down
	}
};

