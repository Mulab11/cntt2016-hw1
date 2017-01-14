#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const LL dx[4]={0,1,0,-1};
const LL dy[4]={1,0,-1,0};
class RobotHerb
{
	public:
	LL getdist(int T,vector<int> a)
	{
		LL x=0,y=0,d=0;
		for(int i=0;i<a.size();i++)
		{
			x+=dx[d]*a[i];
			y+=dy[d]*a[i];
			d=(d+a[i])&3;
		}
		//Get the change of the direction after running the program once.
		if(d==0)return T*(max(x,-x)+max(y,-y));//do not change the direction, simply add all distances up.
		else//After running the program 4 times, the robot return to (0,0) and face forward.
		{
			x=y=d=0;
			T%=4;
			while(T--)
			{
				for(int i=0;i<a.size();i++)
				{
					x+=dx[d]*a[i];
					y+=dy[d]*a[i];
					d=(d+a[i])&3;
				}
			}
			return max(x,-x)+max(y,-y);
		}	
	}
};

