#include<bits/stdc++.h>
using namespace std;
int t,r,g,i;
class BigFatInteger
{
	public:
		int minOperations(int A,int B)
		{
			for(i=2;i<=A;r=max(r,(int)ceil(log2(g*B))),g=0,i++)if(A%i==0)for(t++;A%i==0;A/=i)g++;
			return t+r;//素因子个数加倍增次数
		}
};
