#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#define L long long
using namespace std;
class HolyNumbers
{
	int x[1000010],s[1000010],p;
	inline long long dfs(int i,long long k)    //求出1-k中只包含后i个质数的数的个数 
	{
		if(!i || k<x[i])    //只能选1 
		  return 1;
		if((L)x[i]*x[i]>k)  //单个质数和1 
		  return s[min(k,1000000ll)]-s[x[i]-1]+1;
		long long ans=0;
		ans=dfs(i-1,k);
		for(k/=x[i];k;k/=(L)x[i]*x[i])    //暴力枚举所有奇数幂 
		  ans+=dfs(i-1,k);
		return ans;
	}
public:
	long long count(long long n,int m)
	{
		int i,j;
		for(i=m;i>1;i--)
		  {
		   for(j=2;j*j<=i;j++)
		     if(i%j==0)
		       break;
		   if(j*j>i)
		     {
		      x[++p]=i;
		      s[i]++;
			 }
		  }
		for(i=1;i<=1000000;i++)
		  s[i]+=s[i-1];            //s[i]表示<=i的质数个数 
		return dfs(p,n);
	}
};
