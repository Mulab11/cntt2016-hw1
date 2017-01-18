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

class LeftRightDigitsGame2
{
private:
	int n;
	string f[60][60];//f[i][j]: digits [0, i) > lowerBound [j, j + i), min string [0, i)
	bool eq[60][60];//eq[i][j]: if digits [0, i) == lowerBound [j, j + i)
	bool ex[60][60];//ex[i][j]: if f[i][j] exists
	string mn[60];//mn[i]: digits [0, i) -> minimum number
public:
	string minNumber(string digits, string lowerBound)
	{
		n = digits.size();
		memset(ex, false, sizeof(ex));//!(empty > empty)
		memset(eq, false, sizeof(eq));
		for(int j = 0; j < n; j++)
			eq[0][j] = true;//empty == empty
		mn[0] = "";//empty
		for(int i = 1; i <= n; i++)
		{
			mn[i] = min(mn[i - 1] + digits[i - 1], digits[i - 1] + mn[i - 1]);
			for(int j = 0; i + j <= n; j++)
			{
				//put digits[i - 1] to the left or to the right
				const string lB = lowerBound.substr(j, i);
				if(eq[i - 1][j])
				{
					if(digits[i - 1] == lB[i - 1])
						eq[i][j] = true;//right
					else if(digits[i - 1] > lB[i - 1])
						ex[i][j] = true, f[i][j] = lB.substr(0, i - 1) + digits[i - 1];//right
				}
				if(ex[i - 1][j] && (!ex[i][j] || f[i - 1][j] + digits[i - 1] < f[i][j]))
					ex[i][j] = true, f[i][j] = f[i - 1][j] + digits[i - 1];//right
				if(digits[i - 1] == lB[0])
				{
					if(eq[i - 1][j + 1])
						eq[i][j] = true;//left
					if(ex[i - 1][j + 1] && (!ex[i][j] || digits[i - 1] + f[i - 1][j + 1] < f[i][j]))
						ex[i][j] = true, f[i][j] = digits[i - 1] + f[i - 1][j + 1];//left
				}
				else if(digits[i - 1] > lB[0] && (!ex[i][j] || digits[i - 1] + mn[i - 1] < f[i][j]))
					ex[i][j] = true, f[i][j] = digits[i - 1] + mn[i - 1];//left
			}
		}
		return eq[n][0] ? lowerBound : ex[n][0] ? f[n][0] : "";
	}
};

