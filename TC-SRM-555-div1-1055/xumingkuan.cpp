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
class MapGuessing
{
	private:
	int n, mn, mx, now, len, numPos;
	int st[60], ed[60];
	long long a[60];
	int bitcnt(long long x) const
	{
		int ret = x & 1;
		while(x >>= 1)
			ret += x & 1;
		return ret;
	}
	long long run(vector <string> code, int start)//run the program with "start" as the leftest cell reached
	{
		memset(st, -1, sizeof(st));
		now = start - mn;
		int contradiction_count = 0;
		long long ret = 0;//we can reach the goal before any commands
		long long mask = 0;
		for(int i = 0; i < code.size(); i++)//enumerate the time to reach the goal
			for(int j = 0; j < code[i].size(); j++)
				switch(code[i][j])
				{
					case '0': case '1':
						mask |= (1ll << now);//write at place "now"
						if(st[now] + ed[now] == 1)
							contradiction_count--;
						st[now] = code[i][j] - '0';
						if(st[now] + ed[now] == 1)
							contradiction_count++;
						if(!contradiction_count)
							ret = mask;
						break;
					case '<':
						now--;
						break;
					case '>':
						now++;
						break;
				}
		return ret;
	}
	bool getCode(vector <string> code)
	{
		now = mn = mx = 0;
		for(int i = 0; i < code.size(); i++)
			for(int j = 0; j < code[i].size(); j++)//get the range of head
				switch(code[i][j])
				{
					case '<':
						if(--now < mn)
							if(mx - (mn = now) >= n)//leave the tape
								return false;
						break;
					case '>':
						if(++now > mx)
							if((mx = now) - mn >= n)
								return false;
						break;
				}
		len = mx - mn + 1;
		numPos = n - len + 1;//number of starting positions
		for(int i = 0; i < numPos; i++)
			a[i] = run(code, i);
		return true;
	}
	long long search(int pos, long long val)
	{
		if(pos == numPos)
			return 1ll << bitcnt(val);
		if(!val)
			return 0;//notice: search(numPos, 0) = 2^0 = 1, but search(other, 0) = 2^?*(2^0-2^0) = 0
		return search(pos + 1, val) - search(pos + 1, val & a[pos]);//inclusion-exclusion principle
	}
	public:
	long long countPatterns(string goal, vector<string> code)
	{
		n = goal.size();
		for(int i = 0; i < n; i++)
			ed[i] = goal[i] - '0';
		if(!getCode(code))
			return 0;
		return (1ll << n) - search(0, (1ll << n) - 1);
	}
};

