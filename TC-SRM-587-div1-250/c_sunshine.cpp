#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

class JumpFurther
{
	public:
	
	int furthest(int N,int badStep)
	{
		//We can simply add all numbers in [1,n]
		//If we are to walk on a badStep, we can always skip the first step to avert it
		int ans=0,flag=0;
		for(int i=0;i<=N;i++)
			flag|=(ans+=i)==badStep;
		ans-=flag;
		return ans;
	}
};

