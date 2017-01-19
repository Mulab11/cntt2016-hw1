#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class XorAndSum
{
public:
	long long maxSum(vector<long long> x)
	{
		int n=x.size();
		int i,j;
		long long k;
		//高斯消元求线性基 
		for(k=(1ll<<60),i=0;k>0;k>>=1)
		  {
		   for(j=i;j<n;j++)
		     if(x[j]&k)
		       break;
		   if(j==n)
		     continue;
		   swap(x[i],x[j]);
		   for(j=0;j<n;j++)
		     if(i!=j && (x[j]&k))
		       x[j]^=x[i];
		   i++;
		  }
		for(j=1;j<i;j++)
		  x[0]^=x[j];
		for(j=1;j<n;j++)
		  x[j]^=x[0];
		for(i=0,k=0;i<n;i++)
		  k+=x[i];
		return k;
    }
};
