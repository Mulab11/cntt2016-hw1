#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
class FoxAndFencing
{
public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
	{
		string a = "Ciel", b = "Liss", c = "Draw";
		int atk1 = mov1 + rng1;
		int atk2 = mov2 + rng2; 
		if(d <= atk1) //第一步可以结束游戏 
			return a;
		if(atk1 == atk2) //判断攻击相等情形 
			return c;
		if(atk1 < atk2) //判断后手攻击范围更大情形 
		{
			if(mov1 < mov2)
			{
				if(atk1 + mov1 + 1 <= atk2)
					return b;
				return c;
			}
			if(d + mov1 <= atk2)
				return b;
			return c;
		}
		if(mov2 < mov1 && atk2 + mov2 + 1 <= atk1) //判断先手攻击范围更大情形 
			return a;
		return c;
	}
};