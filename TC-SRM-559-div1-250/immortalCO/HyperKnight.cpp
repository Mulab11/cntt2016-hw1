#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

void cmin(int &a, int b){a > b ? a = b : 0;}
void cmax(int &a, int b){a < b ? a = b : 0;}
class HyperKnight
{
public:
	ll countCells(int a, int b, int n, int m, int k)
	{
		ll ans = 0;
		int X[] = {+a, +a, -a, -a, +b, +b, -b, -b};
		int Y[] = {+b, -b, +b, -b, +a, -a, +a, -a};
		for(int s = 0; s != (1 << 8); ++s)
		{
			int xl = 1, xr = n, yl = 1, yr = m;
			if(s & (1 << 0)) cmax(xl, 1 + a); else cmin(xr, 1 + a - 1);
			if(s & (1 << 1)) cmax(xl, 1 + b); else cmin(xr, 1 + b - 1);
			if(s & (1 << 2)) cmin(xr, n - a); else cmax(xl, n - a + 1);
			if(s & (1 << 3)) cmin(xr, n - b); else cmax(xl, n - b + 1);
			if(s & (1 << 4)) cmax(yl, 1 + a); else cmin(yr, 1 + a - 1);
			if(s & (1 << 5)) cmax(yl, 1 + b); else cmin(yr, 1 + b - 1);
			if(s & (1 << 6)) cmin(yr, m - a); else cmax(yl, m - a + 1);
			if(s & (1 << 7)) cmin(yr, m - b); else cmax(yl, m - b + 1);
			if(xl > xr || yl > yr) continue;
			int c = 0;
			for(int i = 0; i != 8; ++i)
				if(1 <= xl + X[i] && xr + X[i] <= n
				   && 1 <= yl + Y[i] && yr + Y[i] <= m)
					++c;
			if(c == k) ans += (xr - xl + 1ll) * (yr - yl + 1ll);
		}
		return ans;
	}
}   user;
