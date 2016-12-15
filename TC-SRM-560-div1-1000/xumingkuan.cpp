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

class BoundedOptimization
{
	private:
	int n;
	bool e[20][20];//e[i][j]: if expr contains "ij" or "ji"
	int lb[20], ub[20];//lowerBound, upperBound
	int c[20];//coefficient
	int value[20];
	vector <int> chosen;//{x | variable x that value[x] != lb[x] && value[x] != ub[x]}
	double search(int p, int maxSum)//searched variables 'a' ~ ('a' + p - 1)
	{
		if(maxSum < 0)
			return -1e100;
		if(p == n)
		{
			for(int i = 0; i < chosen.size(); i++)
				maxSum -= c[chosen[i]];
			const double add = (chosen.empty() ? 0 : (double)maxSum / chosen.size());
			double ret = 0;//chosen * not chosen
			double tmp = 0;//chosen * chosen
			for(int i = 0; i < chosen.size(); i++)
			{
				const double now = add + c[chosen[i]];//value[chosen[i]]
				if(now < lb[chosen[i]] - 1e-7 || now > ub[chosen[i]] + 1e-7)
					return -1e100;
				ret += now * (c[chosen[i]] - now / 2);
				tmp += now;
			}
			ret += tmp * tmp / 2;//\sigma_{i<j}{value[i]*value[j]} = 1/2({\sigma_i{value[i]}}^2 - \sigma_i{value[i]}^2);
			return ret;
		}
		bool canChoose = true;
		for(int i = 0; i < chosen.size(); i++)
			if(!e[p][chosen[i]])//for every chosen variable u and v, expr should contain "uv" or "vu", otherwise we don't need to choose either u or v.
			{
				canChoose = false;
				break;
			}
		double ret = -1e100;
		if(canChoose)
		{
			value[p] = 0;
			chosen.push_back(p);
			ret = max(ret, search(p + 1, maxSum));
			chosen.pop_back();
		}
		int tmp = 0;
		for(int i = 0; i < p; i++)
			if(e[p][i])
				tmp += value[i];
		value[p] = lb[p];//use lower bound
		for(int i = 0; i < n; i++)
			if(e[p][i])
				c[i] += value[p];
		ret = max(ret, tmp * value[p] + search(p + 1, maxSum - value[p]));
		for(int i = 0; i < n; i++)
			if(e[p][i])
				c[i] -= value[p];
		value[p] = ub[p];//use upper bound
		for(int i = 0; i < n; i++)
			if(e[p][i])
				c[i] += value[p];
		ret = max(ret, tmp * value[p] + search(p + 1, maxSum - value[p]));
		for(int i = 0; i < n; i++)
			if(e[p][i])
				c[i] -= value[p];
		value[p] = 0;
		return ret;
	}
	public:
	double maxValue(vector<string> expr, vector<int> lowerBound, vector<int> upperBound, int maxSum)
	{
		//begin initialize
		string expr1;
		for(int i = 0; i < expr.size(); i++)
			expr1 += expr[i];
		memset(e, false, sizeof(e));
		for(int i = 0; i < expr1.size(); i += 3)
		{
			const int u = expr1[i] - 'a', v = expr1[i + 1] - 'a';
			e[u][v] = e[v][u] = true;
		}
		n = lowerBound.size();
		for(int i = 0; i < n; i++)
		{
			lb[i] = lowerBound[i];
			ub[i] = upperBound[i];
		}
		chosen.clear();
		memset(c, 0, sizeof(c));
		memset(value, 0, sizeof(value));
		//end initialize
		return search(0, maxSum);//O(3^n*n)
	}
};

