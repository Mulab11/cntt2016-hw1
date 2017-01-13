#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

class PiecewiseLinearFunction
{
private:
	vector<pair<int, int> > a;
public:
	int maximumSolutions(vector<int> Y)
	{
		for(int i = 0; i < Y.size() - 1; i++)//consider the difference of number of solutions (answer must be a multiple of 0.5)
		{
			if(Y[i] == Y[i + 1])//infinitely many solutions
				return -1;
			a.push_back(make_pair(min(Y[i], Y[i + 1]) * 2 + (i != Y.size() - 2 && Y[i] > Y[i + 1]), 1));
			a.push_back(make_pair(max(Y[i], Y[i + 1]) * 2 + (i == Y.size() - 2 || Y[i] > Y[i + 1]), -1));
		}
		sort(a.begin(), a.end());
		int ans = 0, now = 0;
		for(int i = 0; i < a.size(); i++)//get max prefix sum
			if((now += a[i].second) > ans)
				ans = now;
		return ans;
	}
};

