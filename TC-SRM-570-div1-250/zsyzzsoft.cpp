#include <algorithm>
using namespace std;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
class RobotHerb
{
public:
	long long getdist(int t, vector<int> a)
	{
		long long x = 0, y = 0;
		int d = 0;
		for(int j = 0; j < 4; j++)
		{
			for(int i = 0; i < a.size(); d = (d + a[i++]) % 4)
				x += a[i] * dx[d], y += a[i] * dy[d];
		}
		x *= t / 4, y *= t / 4; //此时方向一定恢复初始状态 
		t %= 4;
		for(int j = 0; j < t; j++) //模拟剩下的部分 
		{
			for(int i = 0; i < a.size(); d = (d + a[i++]) % 4)
				x += a[i] * dx[d], y += a[i] * dy[d];
		}
		return abs(x) + abs(y);
	}
};
