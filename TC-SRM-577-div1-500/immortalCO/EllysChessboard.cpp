#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;


bool map[16][16];
int f[16][16][16][16];

int mx3(int a, int b, int c) {return a > b ? (a > c ? a : c) : (b > c ? b : c);}

int F(int xl, int xr, int yl, int yr)
{
	if(xl == xr && yl == yr) return 0;
	int &ans = f[xl][xr][yl][yr];
	if(ans) return ans - 1;
	ans = 1000000000;
	int tmp;
	if(xl != xr)
	{
		tmp = F(xl + 1, xr, yl, yr); for(int y = yl; y <= yr; ++y) if(map[xl][y]) tmp += mx3(xr - xl, yr - y, y - yl); if(ans > tmp) ans = tmp;
		tmp = F(xl, xr - 1, yl, yr); for(int y = yl; y <= yr; ++y) if(map[xr][y]) tmp += mx3(xr - xl, yr - y, y - yl); if(ans > tmp) ans = tmp;
	}
	if(yl != yr)
	{
		tmp = F(xl, xr, yl + 1, yr); for(int x = xl; x <= xr; ++x) if(map[x][yl]) tmp += mx3(yr - yl, xr - x, x - xl); if(ans > tmp) ans = tmp;
		tmp = F(xl, xr, yl, yr - 1); for(int x = xl; x <= xr; ++x) if(map[x][yr]) tmp += mx3(yr - yl, xr - x, x - xl); if(ans > tmp) ans = tmp;
	}
	return ans++;
}

class EllysChessboard
{
public:
	int minCost(vector<string> s)
	{
		for(int i = 0; i != 8; ++i)
			for(int j = 0; j != 8; ++j)
				if(s[i][j] == '#')
					map[i + j][i - j + 7] = 1;
		return F(0, 14, 0, 14);
	}
}	user;
