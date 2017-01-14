#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

class TheBrickTowerEasyDivOne
{
	public:
	
	int find(int redCount,int redHeight,int blueCount,int blueHeight)
	{
		//1.i*redHeight+i*blueHeight
		//2.i*redHeight+(i-1)*blueHeight
		//3.(i-1)*redHeight+i*blueHeight
		if(redHeight==blueHeight)//2,3 will count some buildings more than one times, when redHeight=blueHeight.
			return min(redCount,blueCount)*2+(redCount!=blueCount);
		return min(blueCount+1,redCount)+min(redCount+1,blueCount)+min(redCount,blueCount);
	}
	
};

