#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

class BigFatInteger
{
	public:
	int minOperations(int A,int B)
	{
		int cnt=0,mx=0;
		//Operation 1 must be used at least once for each prime factor of A^B
		//Each prime factor of C is independent when we use operation 2, and we can do all prime factors at the same time.
		//If the current number contains p^r, we can change r to [r,2r] in one operation 2.
		//So the minimum number of operation 2 is max{ceil(log_2 r)}.
		for(int i=2;i<=A;i++)
			if(A%i==0)
			{
				cnt++;//the number of distinct prime factors.
				int r=0,t=0;
				while(A%i==0)
					A/=i,r++;
				r*=B;
				for(t=0;1<<t<r;t++);//get ceil(log_2 r)
				mx=max(mx,t);
			}
		return cnt+mx;
	}
};

