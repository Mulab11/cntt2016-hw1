#include <bits/stdc++.h>

using namespace std;

class PiecewiseLinearFunction
{
public:
	int maximumSolutions(vector<int> Y)
	{
		for(int i = 0;i < Y.size() - 1;i ++)
			if (Y[i] == Y[i + 1]) return -1; //infinity numbers
		vector<int> ava;
		int ans = 0;
		for(int i = 0;i < Y.size();i ++)
			for(int type = 0;type < 3;type ++) //the crucial point may only be in U(x0,p)
			{
				double cr = Y[i];
				if (!type) cr -= 0.5;
				if (type == 2) cr += 0.5;
				int co = 0;
				for(int j = 0;j < Y.size() - 1;j ++)
				{
					if (cr > min(Y[j],Y[j + 1]) && cr < max(Y[j],Y[j + 1])) ++ co; else
						if (cr == Y[j] || j + 1 == Y.size() - 1 && cr == Y[j + 1]) ++ co;  //avoid repeative counts
				}
				ans = max(ans,co);
			}
		return ans;
	}
};
