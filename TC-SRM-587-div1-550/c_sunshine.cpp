#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class TriangleXor
{
	public:
	double h[70005];
	int theArea(int W)
	{
		double ans=0;
		if((W&1)==0)ans+=(double)W/4.0;//the top forth of the rectangle
		for(int i=0;i<=W;i++)//the y position of line (0,0)-(W,1) and line (0,1)-(i,0)'s intersection
			h[i]=i/((double)i/W+1);
		for(int i=0;i<W;i++)//the left and right forths of the rectangle
			if((i+1)&1)
				ans+=(h[i+1]-h[i]);
		for(int i=0;i<W;i++)//the bottom forth of the rectangle
		{//divide it in W hierarchies
			double top=W-2*h[i+1];
			double base=W-2*h[i];
			double height=(h[i+1]-h[i])/W;
			//area = bottom * height / 2
			if(i&1)
				ans+=base*height/2;
			else
				ans+=top*height/2;
		}
		cout<<ans<<endl;
		return (int)(ans);
	}
};

