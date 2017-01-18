#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
const int MAXN = 2525;
class GameInDarknessDiv1
{
private:
	int number[55][55];
	queue<pair<int, int> > q;//for bfs
	int depth[MAXN], father[MAXN], height[MAXN], heightpos[MAXN], height2[MAXN], heightfa[MAXN];
	vector<int> son[MAXN];
	int n;//number of points
	int sub;//point P is in subtree sub  <====>  dist(A, P) >= dist(B, P) + 2
	bool dfs(int p)
	{
		int cnt = (heightfa[p] >= 3);
		for(int i = 0; i < son[p].size(); i++)
			if(height[son[p][i]] >= 2)
				cnt++;
		if(cnt >= 3)//>= 3 subtrees with height >= 3
			return true;
		for(int i = 0; i < son[p].size(); i++)
			if(dfs(son[p][i]))
				return true;
		return false;
	}
public:
	string check(vector<string> field)//total time complexity = input
	{
		memset(number, 0, sizeof(number));
		for(int i = 0; i < field.size() && q.empty(); i++)
			for(int j = 0; j < field[0].size() && q.empty(); j++)
				if(field[i][j] == 'A')
					number[i][j] = n = 1, q.push(make_pair(i, j));
		while(!q.empty())//bfs from Alice
		{
			const int x = q.front().first, y = q.front().second;
			q.pop();
			if(field[x][y] == 'B')
			{
				if(depth[number[x][y]] == 1)
					return "Alice wins";
				int tmp = number[x][y];
				for(int i = 1; i <= depth[number[x][y]] / 2 - 1; i++)
					tmp = father[tmp];
				sub = tmp;
			}
			#define check(addx, addy) if(x + (addx) >= 0 && x + (addx) < field.size() && y + (addy) >= 0 && y + (addy) < field[0].size()\
				 && !number[x + (addx)][y + (addy)] && field[x + (addx)][y + (addy)] != '#')\
				{\
					number[x + (addx)][y + (addy)] = ++n;\
					depth[n] = depth[number[x][y]] + 1;\
					father[n] = number[x][y];\
					son[number[x][y]].push_back(n);\
					q.push(make_pair(x + (addx), y + (addy)));\
				}
			check(-1, 0)
			check(1, 0)
			check(0, -1)
			check(0, 1)
			#undef check
		}
		memset(height, 0, sizeof(height));
		memset(height2, 0, sizeof(height2));
		for(int i = n; i > 1; i--)//get subtree height and 2nd max height, reverse bfs order
			if(height[i] + 1 > height[father[i]])
			{
				height2[father[i]] = height[father[i]];
				height[father[i]] = height[i] + 1;
				heightpos[father[i]] = i;
			}
			else if(height[i] + 1 > height2[father[i]])
				height2[father[i]] = height[i] + 1;
		heightfa[1] = 0;
		for(int i = 2; i <= n; i++)//get "subtree father" height, bfs order
			heightfa[i] = max(heightfa[father[i]], heightpos[father[i]] == i ? height2[father[i]] : height[father[i]]) + 1;
		if(dfs(sub))
			return "Bob wins";
		else
			return "Alice wins";
	}
};

