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

class DrawingPointsDivOne
{
	private:
	int n;
	bool a[300][300];//a[i][j] is true if there is an initial point (i, j)
	bool b[300][300];
	public:
	int maxSteps(vector<int> x, vector<int> y)
	{
		n = x.size();
		memset(a, false, sizeof(a));
		for(int i = 0; i < n; i++)
			a[x[i] + 70][y[i] + 70] = true;//make them non-negative
		for(int t = 1; t <= 150; t++)//check if (>= t steps) is ok
		{
			for(int i = 140 + t; i >= 0; i--)
				for(int j = 140 + t; j >= 0; j--)
					if(a[i][j])
						a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 1] = true;
			memcpy(b, a, sizeof(b));
			for(int t1 = t; t1 >= 1; t1--)//simulate
				for(int i = 0; i <= 140 + t1; i++)
					for(int j = 0; j <= 140 + t1; j++)
						b[i][j] = (b[i][j] && b[i + 1][j] && b[i][j + 1] && b[i + 1][j + 1]);
			int cnt = 0;
			for(int i = 0; i <= 140; i++)
				for(int j = 0; j <= 140; j++)
					if(b[i][j])
						cnt++;
			if(cnt != n)//t - 1 steps is ok, but t steps isn't
				return t - 1;
		}
		return -1;//no maximum
	}
};

