#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int o,ans;
struct BigFatInteger
{
	int minOperations(int a,int b)
	{
		for(int i=2;i<=a;i++)
		if(a%i==0)
		{
			ans++;
			int x=0;
			while(a%i==0) a/=i,x+=b;
			o=max(o,x);
		}
		if(o>1) ans+=log2(o-1)+1;
		return ans;
	}
};