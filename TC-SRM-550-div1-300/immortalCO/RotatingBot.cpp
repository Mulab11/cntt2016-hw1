#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

char vis[5010][5010];

class RotatingBot
{
public:
	int minArea(vector<int> mov)
	{
		const int cx[] = {1, 0, -1, 0};
		const int cy[] = {0, 1, 0, -1};
		int xl = 0, xr = 0, yl = 0, yr = 0, x = 0, y = 0;
		vis[x + 2500][y + 2500] = 1;
		for(int i = 0; i != (int) mov.size(); ++i)
		{
			const int d = i % 4;
			for(int p = mov[i]; p--; )
			{
				x += cx[d];
				y += cy[d];
				if(vis[x + 2500][y + 2500]) return -1;
				vis[x + 2500][y + 2500] = 1;
			}
			if(x < xl) xl = x; if(x > xr) xr = x;
			if(y < yl) yl = y; if(y > yr) yr = y;
		}
		x = y = 0;
		vis[2500][2500] = 2;
		for(int i = 0; i != (int) mov.size(); ++i)
		{
			const int d = i % 4;
			for(int p = mov[i]; p--; )
			{
				x += cx[d];
				y += cy[d];
				vis[x + 2500][y + 2500] = 2;
			}
			if(!(vis[x + cx[d] + 2500][y + cy[d] + 2500] == 2
				 || x + cx[d] < xl || x + cx[d] > xr
				 || y + cy[d] < yl || y + cy[d] > yr
				 || i + 1 == (int) mov.size())) return -1;
		}
		return (xr - xl + 1) * (yr - yl + 1);
	}
	
}	user;
