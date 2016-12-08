#include<bits/stdc++.h>
using namespace std;
class TriangleXor
{
	public:
		int theArea(int x)
		{
			double s=.5*x*(x+1);
			for(int i=1;i<=x;i++)if(i&1)s-=1.*x*x/(x+i)*(x-i+1);else s+=1.*x*x/(x+i)*(x-i+1);//容斥			
			return floor(s);
		}
};
