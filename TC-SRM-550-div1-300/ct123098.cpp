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

const int MAXM = 1000;
const int dx[] = {0, -1, 0, 1};
const int dy[] = {1, 0, -1, 0};

class RotatingBot
{
	public:
	
	bool vis[MAXM][MAXM];
	int x, y, l, r, t, b;
	
	bool check(int x, int y)
	{
		if(x < t || x > b || y < l || y > r)
			return false;
		return !vis[x][y];
	}
	
	int minArea(vector<int> moves)
	{
		l = r = x = 500, t = b = y = 500;
		for(int i = 0, dir = 0; i < moves.size(); i++, dir = (dir + 1) % 4)
		{
			x += dx[dir] * moves[i], y += dy[dir] * moves[i];
			t = min(t, x), b = max(b, x);
			l = min(l, y), r = max(r, y);
		}
//		cout << endl;
//		cout << t << ' ' << b << endl;
//		cout << l << ' ' << r << endl;
		x = 500, y = 500;
		vis[x][y] = true;
		for(int i = 0, dir = 0; i < moves.size(); i++, dir = (dir + 1) % 4)
		{
			for(int j = 1; j <= moves[i]; j++)
			{
				if(!check(x + dx[dir], y + dy[dir]))
					return -1;
				x += dx[dir], y += dy[dir];
				vis[x][y] = true;
			}
			if(i < moves.size() - 1 && check(x + dx[dir], y + dy[dir]))
				return -1;
		}
		return (b - t + 1) * (r - l + 1);
	}
};

