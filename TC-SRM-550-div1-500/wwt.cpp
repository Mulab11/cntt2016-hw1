/*
打表可以发现，这幅图其实就是一个三角形，复制三份，中间挖个洞，造个新的，不停这样下去。那么假设我们要求char(t,x,y)，
我们找到最大的一个2^k < t(2^k步恰好形成一个大三角形)，找到(x,y)属于哪个区域，递归下去。
*/
#include <bits/stdc++.h>

using namespace std;

class CheckerExpansion
{
public:
	char find_char(long long t,long long x,long long y)
	{
		if (!t) return '.';
		if (t == 1) return (!x && !y) ? 'A' : '.';
		if (t == 2)
		{
			if (!x && !y) return 'A';
			if (x == 2 && y == 0) return 'B';
			if (x == 1 && y == 1) return 'B';
			return '.';
		}
		long long p = 1;
		for(;p * 2 < t;p *= 2); //找到是哪个大三角形
		if (x < p * 2 && y < p) return find_char(p,x,y); //左下角的三角形
		if (y < p) return find_char(t - p,x - 2 * p,y); //右下角三角形
		if (x >= p) return find_char(t - p,x - p,y - p);//上方三角形
		return '.';
	}

	vector<string> resultAfter(long long t,long long x0,long long y0,int w,int h)
	{
		vector<string> ret;
		for(int i = 0;i < h;i ++)
		{
			string cur = "";
			for(int j = 0;j < w;j ++)
				cur = cur + find_char(t,x0 + j,y0 + h - i - 1);
			ret.push_back(cur);
		}
		return ret;
	}
};
