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

class Suminator
{
	public:
	stack<pair<int, long long> > s; 
	int findMissing(vector<int> program, int wantedResult)
	{

		for(int i  = 0; i < program.size(); i++)
		{
			int x = program[i];
			if(x == 0 || x == -1)
			{
				pair<int, long long> a = s.empty() ? make_pair(0, 0ll): s.top();
				if(!s.empty()) s.pop();
				pair<int, long long> b = s.empty() ? make_pair(0, 0ll): s.top();
				if(!s.empty()) s.pop();
				s.push(make_pair(a.first + b.first, a.second + b.second));
			}
			else
				s.push(make_pair(0, x));
		}
		pair<int, long long> a = s.empty() ? make_pair(0, 0ll): s.top();
		bool x = a.first;
		long long y = a.second;
		if(y == wantedResult)
			return 0;

		while(!s.empty()) s.pop();
		for(int i  = 0; i < program.size(); i++)
		{
			int x = program[i];
			if(x == -1)
				s.push(make_pair(1, 0));
			else if(x == 0)
			{
				pair<int, long long> a = s.empty() ? make_pair(0, 0ll): s.top();
				if(!s.empty()) s.pop();
				pair<int, long long> b = s.empty() ? make_pair(0, 0ll): s.top();
				if(!s.empty()) s.pop();
				s.push(make_pair(a.first + b.first, a.second + b.second));
			}
			else
				s.push(make_pair(0, x));
		}
		a = s.empty() ? make_pair(0, 0ll): s.top();
		x = a.first, y = a.second;
		if(x == 0)
		{
			if(y == wantedResult)
				return 1;
			return -1;
		}
		else
		{
			y = wantedResult - y;
			if(y > 0)
				return y;
			return -1;
		}

		return 0;
	}
};

