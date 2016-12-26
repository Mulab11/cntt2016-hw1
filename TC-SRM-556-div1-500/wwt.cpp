/*
从后往前做。假设当前做到第i位，要求>=lower的最小值，那么考虑将i放到第一位和最后一位，分类讨论一下可以变成一个求i-1;
//lower'的子问题，记忆化搜索。
*/
#include <bits/stdc++.h>

using namespace std;

class LeftRightDigitsGame2
{
public:
	map<string,string> sav[55];
	string al;

	string solve(int cur,string lower)
	{
		if (cur == 0)
		{
			if (al[0] < lower[0]) return "";
			return al.substr(0,1);
		}
		auto p = sav[cur].find(lower);
		if (p != sav[cur].end()) return (*p).second; 
		string tmp = "",bak,els;
		els = lower;
		//放到第一位，根据大小关系确定剩下的大小
		if (al[cur] > lower[0])
		{
			bak = solve(cur - 1,string(cur,'0' - 1));
			if (bak != "") tmp = al[cur] + bak;
		}
		if (al[cur] == lower[0])
		{
			bak = solve(cur - 1,lower.substr(1));
			if (bak != "") tmp = al[cur] + bak;
		}
		//放到最后一位
		bool ok = 1;
		if (al[cur] < lower[lower.length() - 1])
		{
			int l = lower.length() - 1;
			lower[l - 1] ++; //lower+1
			for(int i = l - 1;i >= 0;i --)
			{
				if (lower[i] > '9')
				{
					if (!i) {ok = 0;break;}
					lower[i - 1] ++;
					lower[i] -= 10;
				}
			}
		}
		if (ok)
		{
			bak = solve(cur - 1,lower.substr(0,lower.length() - 1));
			if (bak != "")
			{
				if (tmp == "") tmp = bak + al[cur]; else 
					tmp = min(tmp,bak + al[cur]);
			}
		}
		sav[cur][els] = tmp;
		return tmp;
	}

	string minNumber(string digits, string lowerBound)
	{
		for(int i = 0;i < digits.size();i ++) sav[i].clear();
		al = digits;
		string tmp = solve(digits.length() - 1,lowerBound);
		cout << tmp;
		return tmp;
	}
};
