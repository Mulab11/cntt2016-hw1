#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
class FoxPaintingBalls
{
	public:
	
	LL theMax(LL R,LL G,LL B,int N)
	{
		if(N==1)return R+G+B;
		LL cnt=(LL)N*(N+1)/6;
		if(N%3!=1)//The number of each color of balls in each triangle is N*(N+1)/6.
			return min(min(R,G),B)/cnt;
		LL low=-1,high=R+G+B+1,mid;
		while(low+1<high)//Use dichotomy to determine the answer.
		{
			mid=low+high>>1;
			//Each triangle contains one more ball in any color.
			if(min(min(R,G),B)/cnt>=mid&&R+G+B-3*cnt*mid>=mid)
				low=mid;
			else high=mid;
		}
		return low;
	}
};

