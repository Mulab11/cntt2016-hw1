#include <algorithm>
#include <math.h>
using namespace std;
const int p = 100007;
struct Point
{
	double x, y;
	Point() {x = y = 0; }
	Point(double _x, double _y) {x = _x, y = _y; }
	Point Vertical() const
	{
		return Point(-y, x);
	}
	Point operator + (const Point &_pt) const
	{
		return Point(x + _pt.x, y + _pt.y);
	}
	Point operator - (const Point &_pt) const
	{
		return Point(x - _pt.x, y - _pt.y);
	}
	Point operator * (double p) const
	{
		return Point(x * p, y * p);
	}
	Point operator / (double p) const
	{
		return Point(x / p, y / p);
	}
	double operator * (const Point &_pt) const
	{
		return x * _pt.x + y * _pt.y;
	}
	double operator ^ (const Point &_pt) const
	{
		return x * _pt.y - y * _pt.x;
	}
};
int cnt[222][222], f[222][222][2], g[222][222], h[222][222];
class FencingPenguins
{
public:
	int n, m;
	int flag[128];
	bool con[222][222];
	Point pt[222];
	Point Get(int ind)
	{
		return Point(cos(M_PI * 2.0 * ind / n), sin(M_PI * 2.0 * ind / n));
	}
	int countWays(int _n, int r, vector<int> x, vector<int> y, string color)
	{
		n = _n, m = x.size();
		for(int i = 0; i < m; i++)
			pt[i] = Point(x[i], y[i]) / r;
		for(int i = 0; i < n; i++) //所有点必须都在多边形内部 
		{
			for(int j = 0; j < m; j++)
			{
				if(((Get(i + 1) - Get(i)) ^ (pt[j] - Get(i))) <= 0)
					return 0;
			}
		}
		for(int i = 0; i < n; i++) //预处理每条对角线是否穿过同色点组 
		{
			for(int j = i + 1; j < n; j++)
			{
				con[i][j] = true;
				for(int k = 0; k < m; k++)
					flag[(int)color[k]] = -1;
				for(int k = 0; k < m; k++)
				{
					int div = ((Get(i) - Get(j)) ^ (pt[k] - Get(j))) > 0;
					cnt[i][j] += div;
					int c = color[k];
					if(flag[c] == -1)
						flag[c] = div;
					else if(flag[c] != div)
						con[i][j] = false;
				}
			}
		}
		for(int i = 1; i < n; i++)
			g[i][i - 1] = 1;
		for(int i = 0; i < n; i++)
			h[i][i] = f[i][i][1] = g[i][i] = 1;
		for(int d = 1; d < n; d++)
		{
			for(int i = 0, j = d; j < n; i++, j++)
			{
				for(int k = i + 1; k < j; k++) //枚举当前环的下一个顶点 
				{
					if(cnt[i][k] == cnt[i + 1][k - 1]) //间隙中的点没有被遗漏 
					{
						int cover = cnt[i][k] + cnt[k][j] < cnt[i][j]; //新增一条边后是否有点被覆盖 
						h[i][j] = ((long long)g[i + 1][k - 1] * f[k][j][cover] + h[i][j]) % p;
						f[i][j][1] = ((long long)g[i + 1][k - 1] * f[k][j][1] + f[i][j][1]) % p;
					}
				}
				f[i][j][0] = h[i][j];
				if(cnt[i][j] == cnt[i + 1][j - 1])
					f[i][j][1] = (f[i][j][1] + g[i + 1][j - 1]) % p; //结束当前环 
				if(!con[i][j])
					h[i][j] = 0;
				if(cnt[i][j] == 0) //区域内没有可覆盖的点 
				{
					f[i][j][0] = 0;
					h[i][j] = 0;
					g[i][j] = 1;
					continue;
				}
				if(cnt[i][j] == cnt[i][j - 1])
					g[i][j] = g[i][j - 1];
				for(int k = i; k < j; k++)
				{
					if(k == i)
						g[i][j] = (h[k][j] + g[i][j]) % p;
					else if(cnt[k][j] == cnt[i][j] - cnt[i][k - 1])
						g[i][j] = ((long long)h[k][j] * g[i][k - 1] + g[i][j]) % p;
				}
			}
		}
		return g[0][n - 1];
	}
};
