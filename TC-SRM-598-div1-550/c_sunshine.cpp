#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

class FoxAndFencing
{
	public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
	{
		//I don't know the significance of this problem, but I think the following conclusions are obvious.
		if(d<=mov1+rng1)
			return "Ciel";
		if(d+mov1<=mov2+rng2)
			return "Liss";
		if(mov1>mov2&&mov2*2+rng2<mov1+rng1)
			return "Ciel";
		if(mov2>mov1&&mov1*2+rng1<mov2+rng2)
			return "Liss";
		return "Draw";
	}
};

