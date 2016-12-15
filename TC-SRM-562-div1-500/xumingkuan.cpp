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
class Point
{
	public:
		int x, y;
		Point(){}
		Point(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
		Point operator +(const Point &b) const
		{
			return Point(x + b.x, y + b.y);
		}
		Point operator -(const Point &b) const
		{
			return Point(x - b.x, y - b.y);
		}
		Point& operator +=(const Point &b)
		{
			return *this = *this + b;
		}
		Point& operator -=(const Point &b)
		{
			return *this = *this - b;
		}
};
long long det(const Point &a, const Point &b)
{
	return (long long)a.x * b.y - (long long)a.y * b.x;
}
vector <int> concatenate(const vector <string> &vec)
{
	static char buf[10101];
	char *head = buf, *tail = buf;
	for(int i = 0; i < vec.size(); i++)
		tail += sprintf(tail, "%s", vec[i].c_str());
	vector <int> ret;
	while(1)
	{
		char ch = *head++;
		if(head > tail)
			return ret;
		while(ch < '0' || ch > '9')
		{
			ch = *head++;
			if(head > tail)
				return ret;
		}
		int tmp = 0;
		while(ch >= '0' && ch <= '9')
		{
			tmp = tmp * 10 + ch - '0';
			ch = *head++;
		}
		ret.push_back(tmp);
	}
}
class CheckerFreeness
{
	private:
	Point white[233], black[233];
	int wn, bn;//white number, black number
	vector <int> tmp, le, ri;
	bool pos[233][233][233];
	public:
	string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY)
	{
		tmp = concatenate(whiteX);
		wn = tmp.size();
		for(int i = 0; i < wn; i++)
			white[i].x = tmp[i];
		tmp = concatenate(whiteY);
		for(int i = 0; i < wn; i++)
			white[i].y = tmp[i];
		tmp = concatenate(blackX);
		bn = tmp.size();
		for(int i = 0; i < bn; i++)
			black[i].x = tmp[i];
		tmp = concatenate(blackY);
		for(int i = 0; i < bn; i++)
			black[i].y = tmp[i];
		for(int i = 0; i < bn; i++)
			for(int j = i + 1; j < bn; j++)
				for(int k = 0; k < wn; k++)
					pos[i][j][k] = pos[j][i][k] = (det(white[k] - black[i], black[j] - black[i]) < 0);
		for(int i = 0; i < wn; i++)
			for(int j = i + 1; j < wn; j++)
			{
				le.clear();
				ri.clear();
				for(int k = 0; k < bn; k++)
					if(det(black[k] - white[i], white[j] - white[i]) < 0)//pruning: a segment of two black points on the same side of the white segment won't intersect it.
						le.push_back(k);
					else
						ri.push_back(k);
				for(int k = 0; k < le.size(); k++)
					for(int l = 0; l < ri.size(); l++)
						if(pos[le[k]][ri[l]][i] != pos[le[k]][ri[l]][j])
							return "NO";//there is a checker if and only if a white segment intersects a black segment.
			}
		return "YES";
		//O(W^2B^2).  <= about 1.3s per test case.
	}
};

