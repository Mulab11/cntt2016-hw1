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

using namespace std;
const int a[4][2] = {
	{0, 1},//right
	{-1, 0},//up
	{0, -1},//left
	{1, 0}};//down
class RotatingBot
{
	private:
	bool f[1500][1500];//true if it's a visited cell
	int x, y;//position
	int e[4];//right, up, left, down; e.g. e[0] = max(y)
	bool lim[4];//lim[i] is true if e[i] is the edge of the grid
	public:
	int minArea(vector<int> moves)
	{
		memset(f, false, sizeof(f));
		x = y = e[0] = e[1] = e[2] = e[3] = 750;
		f[x][y] = true;//visit the starting cell
		memset(lim, false, sizeof(lim));
		for(int i = 0; i < moves.size(); i++)
		{
			const int pos = i % 4;
			for(int j = 1; j <= moves[i]; j++)
			{
				if(f[x + j * a[pos][0]][y + j * a[pos][1]])//visited
					return -1;
				f[x + j * a[pos][0]][y + j * a[pos][1]] = true;
			}
			x += moves[i] * a[pos][0];//move
			y += moves[i] * a[pos][1];
			if(y > e[0])//update max(y)
			{
				e[0] = y;
				if(lim[0])//previous e[0] is the edge, now out of the grid
					return -1;
				lim[0] = true;//rotate after move i, so it must be the edge (case when i == moves.size() - 1 doesn't matter)
			}
			if(x < e[1])
			{
				e[1] = x;
				if(lim[1])
					return -1;
				lim[1] = true;
			}
			if(y < e[2])
			{
				e[2] = y;
				if(lim[2])
					return -1;
				lim[2] = true;
			}
			if(x > e[3])
			{
				e[3] = x;
				if(lim[3])
					return -1;
				lim[3] = true;
			}
			if(i != moves.size() - 1 && !f[x + a[pos][0]][y + a[pos][1]])//not the last move && won't automatically rotate
			{
				lim[pos] = true;//must be the edge
				if(e[pos] != (pos & 1 ? x : y))//but it isn't at the edge now
					return -1;
			}
		}
		return (e[0] - e[2] + 1) * (e[3] - e[1] + 1);//min grid which contains all visited cells
	}
};

