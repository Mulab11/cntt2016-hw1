#include <bits/stdc++.h>

using namespace std;

class BallsSeparating
{
public:
	void update(int &a,int b)
	{
		if (b > a) a = b;
	}

	int minOperations(vector<int> red, vector<int> green, vector<int> blue)
	{
		static int f[55][8];
		memset(f,200,sizeof f);
		int n = red.size(),sum = 0;
		f[0][0] = 0;
		for(int i = 0;i < n;i ++)
		{		
			sum += red[i] + green[i] + blue[i];
			for(int s = 0;s < 8;s ++) // s denotes whether the color has been chosen
			{
				update(f[i + 1][s | 1],f[i][s] + red[i]); 
				update(f[i + 1][s | 2],f[i][s] + green[i]);
				update(f[i + 1][s | 4],f[i][s] + blue[i]);
				update(f[i + 1][s],f[i][s]);
			}
		}
		if (f[n][7] < 0) return -1; //illegal
		return sum - f[n][7];
	}
};
