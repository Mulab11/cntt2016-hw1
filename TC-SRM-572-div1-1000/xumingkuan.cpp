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
class Node
{
public:
	int from, to;
	Node(){}
	Node(int from, int to): from(from), to(to) {}
};
class NextAndPrev
{
private:
	int to[30];//to[i]: transfer of letter i
	vector<Node> vec;//store transfers
	int nextCost, prevCost;
	int calc()
	{
		int ret = 0;
		for(int i = 0; i < vec.size(); i++)
		{
			int st = i, ed = i;
			while(ed + 1 < vec.size() && vec[ed + 1].to == vec[ed].to)
				ed++;
			if(vec[st].from <= vec[st].to && vec[st].to <= vec[ed].from)
				ret += nextCost * (vec[st].to - vec[st].from) + prevCost * (vec[ed].from - vec[st].to);
			else if(vec[st].from >= vec[st].to)
				ret += prevCost * (vec[ed].from - vec[st].to);
			else
				ret += nextCost * (vec[st].to - vec[st].from);
			i = ed;
		}
		return ret;
	}
public:
	int getMinimum(int nextCost, int prevCost, string start, string goal)//total time complexity: O(n)
	{
		if(start == goal)//doesn't need to change
			return 0;
		this->nextCost = nextCost;
		this->prevCost = prevCost;
		memset(to, -1, sizeof(to));
		for(int i = 0; i < start.size(); i++)
		{
			if(to[start[i] - 'a'] != -1 && to[start[i] - 'a'] != goal[i] - 'a')
				return -1;//impossible
			to[start[i] - 'a'] = goal[i] - 'a';
		}
		vec.clear();
		bool eq = true;
		int tmpcnt = 1;
		for(int i = 0; i < 26; i++)
			if(to[i] != -1)
			{
				vec.push_back(Node(i, to[i]));
				if(vec.size() >= 2 && vec[vec.size() - 2].to != vec[vec.size() - 1].to)
					eq = false, tmpcnt++;
			}
		if(tmpcnt == 26)//change anything will make it invalid
			return -1;
		if(eq)//change everything to only 1 letter
		{
			int nowto = vec[0].to;
			vec.push_back(vec[0]);
			int ans = 1010101010;
			for(int i = 0; i < vec.size() - 1; i++)//use next and prev
				ans = min(ans, (nowto - vec[i + 1].from + 26) % 26 * nextCost + (vec[i].from - nowto + 26) % 26 * prevCost);
			int st = 0;
			vec.back().from += 26;
			while(vec[st].from < nowto)
				st++;
			ans = min(ans, ((st == 0 ? vec[vec.size() - 2].from : vec[st - 1].from) - nowto + 26) % 26 * prevCost);//use only prev
			ans = min(ans, (nowto - (vec[st].from == nowto ? vec[st + 1].from : vec[st].from) + 26) % 26 * nextCost);//use only next
			return ans;
		}
//		for(int i = 0; i < vec.size(); i++)
//			printf("%d %d->%d\n", i, vec[i].from, vec[i].to);
		int st = 0;
		while(vec[st].to == vec[vec.size() - 1].to)
		{
			vec.push_back(vec[st++]);
			vec.back().from += 26;
		}
		vec.erase(vec.begin(), vec.begin() + st);
		//now the vector's first element's "to" and last's are different.
		if(vec[0].to < vec[0].from)
			vec[0].to += 26;
		int tmp = vec[0].to;
		for(int i = 1; i < vec.size(); i++)
		{
			if(tmp % 26 > vec[i].to % 26)
				tmp += 26;
			vec[i].to = tmp = tmp - tmp % 26 + vec[i].to % 26;
		}
		if(tmp - vec[0].to > 26)
			return -1;//impossible (over 1 circle, will intersect)
//		for(int i = 0; i < vec.size(); i++)
//			printf("%d %d->%d\n", i, vec[i].from, vec[i].to);
		int ans1 = calc();
		for(int i = 0; i < vec.size(); i++)//adjust: -26
			vec[i].to -= 26;
//		for(int i = 0; i < vec.size(); i++)
//			printf("%d %d->%d\n", i, vec[i].from, vec[i].to);
		int ans2 = calc();
		for(int i = 0; i < vec.size(); i++)//adjust: +26
			vec[i].to += 52;
//		for(int i = 0; i < vec.size(); i++)
//			printf("%d %d->%d\n", i, vec[i].from, vec[i].to);
		int ans3 = calc();
		int ans = min(ans1, min(ans2, ans3));
//		printf("%d %d %d  ans=%d\n", ans1, ans2, ans3, ans);
		return ans;
	}
};

