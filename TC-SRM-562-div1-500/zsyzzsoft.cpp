#include <algorithm>
using namespace std;
struct Point
{
	int x, y;
	Point() {x = y = 0; }
	Point(int _x, int _y) {x = _x, y = _y; }
	Point operator + (const Point &p)
	{
		return Point(x + p.x, y + p.y);
	}
	Point operator - (const Point &p)
	{
		return Point(x - p.x, y - p.y);
	}
	long long operator * (const Point &p)
	{
		return (long long)x * p.y - (long long)y * p.x;
	}
};
class CheckerFreeness
{
public:
	int na, nb;
	Point a[222], b[222];
	vector<int> ha, hb;
	int Parse(const vector<string> &sv, int *ptr)
	{
		int n = 1;
		string str;
		for(int i = 0; i < sv.size(); i++)
			str += sv[i];
		*ptr = 0;
		for(int i = 0; i < str.length(); i++)
		{
			if(str[i] >= '0' && str[i] <= '9')
				*ptr = *ptr * 10 + (str[i] - '0');
			else if(*ptr)
				*(ptr += 2) = 0, n++;
		}
		return n;
	}
	bool Intersect(Point au, Point av, Point bu, Point bv) //判相交 
	{
		return ((bu - au) * (av - au) > 0) ^ ((bv - au) * (av - au) > 0) && ((au - bu) * (bv - bu) > 0) ^ ((av - bu) * (bv - bu) > 0);
	}
	void ConvexHull(int n, Point *p, vector<int> &result) //求凸包 
	{
		pair<int, int> fp = make_pair(0, 0);
		for(int i = 0; i < n; i++)
			fp = max(fp, make_pair(p[i].x, i));
		result.push_back(fp.second);
		for(int i = fp.second; ; )
		{
			int nxt = i ? 0 : 1;
			for(int j = nxt + 1; j < n; j++)
			{
				if(j == i)
					continue;
				if((p[j] - p[i]) * (p[nxt] - p[i]) > 0)
					nxt = j;
			}
			result.push_back(nxt);
			if((i = nxt) == result[0])
				break;
		}
	}
	string isFree(vector<string> sa_x, vector<string> sa_y, vector<string> sb_x, vector<string> sb_y)
	{
		na = Parse(sa_x, &a[0].x);
		Parse(sa_y, &a[0].y);
		nb = Parse(sb_x, &b[0].x);
		Parse(sb_y, &b[0].y);
		if(na <= 1 || nb <= 1)
			return "YES";
		ConvexHull(na, a, ha);
		ConvexHull(nb, b, hb);
		for(int i = 0, ni = 1; i < ha.size(); i++, ni = (ni + 1) % ha.size()) 
		{
			for(int u = 0; u < nb; u++)
			{
				for(int v = u + 1; v < nb; v++)
				{
					if(Intersect(a[ha[i]], a[ha[ni]], b[u], b[v])) //a的凸包在b的内部时，枚举b的任意一条线段与a的凸包判相交即可 
						return "NO";
				}
			}
		}
		for(int u = 0; u < na; u++)
		{
			for(int v = u + 1; v < na; v++)
			{
				for(int j = 0, nj = 1; j < hb.size(); j++, nj = (nj + 1) % hb.size())
				{
					if(Intersect(a[u], a[v], b[hb[j]], b[hb[nj]])) //反之亦然 
						return "NO";
				}
			}
		}
		return "YES";
	}
};
