#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class IncrementAndDoubling
{
	public:
	
	int cntA(int x)
	{return x?1+cntA(x&(x-1)):0;}
	
	int cntB(int x)
	{return x<=1?0:1+cntB(x>>1);}
	
	int getMin(vector<int> desiredArray)
	{
		//It is fastest to create the numbers with Cantor unfold.
		//The only operation is plus 1 and time 2
		//We can multiply all numbers at the same time, but operation plus 1 must be done one by one.
		int A=0,B=0;
		for(int i=0;i<desiredArray.size();i++)
		{
			A+=cntA(desiredArray[i]);//times to plus 1.
			B=max(B,cntB(desiredArray[i]));//times to multiply 2.
		}
		return A+B;
	}
};

