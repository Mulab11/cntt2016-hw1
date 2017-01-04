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
#include <map>
using namespace std;
const int to[4][2] = {//up, right, down, left
	{0, 1}, 
	{1, 0}, 
	{0, -1}, 
	{-1, 0}};
class RobotHerb
{
public:
	long long getdist(int T, vector<int> a)
	{
		int dir = 0, x = 0, y = 0;
		for(int i = 0; i < a.size(); i++)//simulate
		{
			x += to[dir][0] * a[i];//move
			y += to[dir][1] * a[i];
			dir = (dir + a[i]) % 4;//turn
		}
		if(dir == 0)//go straight forward
			return (long long)T * (abs(x) + abs(y));
		if(dir == 2)//go backwards
			return T & 1 ? (abs(x) + abs(y)) : 0;
		return T % 4 == 0 ? 0 : T % 4 == 2 ? (abs(x + y) + abs(x - y)) : (abs(x) + abs(y));//turn left or right
	}
};

