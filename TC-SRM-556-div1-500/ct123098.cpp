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

const int MAXN = 50 + 10;

class LeftRightDigitsGame2
{
	public:
	string a;
	string b;
	string f[MAXN][MAXN][3][3];
	
	string search(int st, int ed, int s1, int s2)
	{
		if(f[st][ed][s1][s2] != "")
			return f[st][ed][s1][s2];
		int x = ed - st;
		string ret = "z", tmp = "";
		if(st == ed)
		{
			if(s1 == 0 || (s1 == 1 && a[x] < b[st]) || (s1 == 1 && a[x] == b[st] && s2 == 0))
				return f[st][ed][s1][s2] = "z";
//		cout << st << ' ' << ed << ' ' << s1 << ' ' << s2 << endl;
			return f[st][ed][s1][s2] = a[x];
		}
		// put front
		int ss1 = 0;
		if(s1 == 0)
			ss1 = 0;
		else if(s1 == 1)
		{
			if(a[x] < b[st]) ss1 = 0;
			else if(a[x] == b[st]) ss1 = 1;
			else ss1 = 2;   
		}
		else
			ss1 = 2;
		tmp = search(st + 1, ed, ss1, s2);
		if(tmp != "z") ret = min(ret, a[x] + tmp);
		
		// put back
		int ss2 = 0;
		if(a[x] < b[ed])
			ss2 = 0;
		else if(a[x] == b[ed])
			ss2 = s2;
		else
			ss2 = 2;
		tmp = search(st, ed - 1, s1, ss2);
		if(tmp != "z") ret = min(ret, tmp + a[x]);	  
//		cout << st << ' ' << ed << ' ' << s1 << ' ' << s2 << ' ' << ret << endl;
		return f[st][ed][s1][s2] = ret;
	}
	
	string minNumber(string digits, string lowerBound)
	{
		a = digits;
		b = lowerBound;
		string ans = search(0, a.size() - 1, 1, 1);
		if(ans == "z")
			return "";
		return ans;
	}
};

