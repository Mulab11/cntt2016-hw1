#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
struct TriangleXor
{
	int theArea(int W)
	{
		int i,j,x,y;
		double ans=1.0*(W+1)*W/2;
		for(i=W-1;i>=0;i--)
		{
			x=W-i;
			if(x%2==1)
			ans-=(1-1.0*x/(x+W))*(i+1)*W;
			else
			ans+=(1-1.0*x/(x+W))*(i+1)*W;
		}
		return (int)ans;
	}
};
/*int main()
{
	TriangleXor P;
	cout<<P.theArea(50000);
}*/