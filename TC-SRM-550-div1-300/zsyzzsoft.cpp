#include <algorithm>
using namespace std;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool vis[2000][2000];
class RotatingBot
{
public:
	int l, r, b, t;
	bool Step(int x, int y) //向前走一步 
	{
		if(vis[x][y])
			return false;
		return vis[x][y] = true;
	}
	bool Turn(int x, int y) //判断能否转向 
	{
		return vis[x][y] || x < l || x > r || y < b || y > t;
	}
	int minArea(vector<int> moves)
	{
		int x = 1000, y = 1000, dir = 3;
		l = x, r = x, b = y, t = y;
		for(int i = 0; i < moves.size(); i++) //更新边界 
		{
			dir = (dir + 1) % 4;
			x += dx[dir] * moves[i], y += dy[dir] * moves[i];
			l = min(l, x);
			r = max(r, x);
			b = min(b, y);
			t = max(t, y);
		}
		x = y = 1000, dir = 3;
		vis[x][y] = true;
		for(int i = 0; i < moves.size(); i++)
		{
			if(i && !Turn(x + dx[dir], y + dy[dir]))
				return -1;
			dir = (dir + 1) % 4; //转向 
			for(int j = 0; j < moves[i]; j++) //模拟 
			{
				if(!Step(x += dx[dir], y += dy[dir]))
					return -1;
			}
		}
		return (r - l + 1) * (t - b + 1);
	}
};