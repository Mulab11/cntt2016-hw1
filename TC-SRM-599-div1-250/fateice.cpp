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
#define inf 1000000000000000000ll
#define eps 1e-9
using namespace std;
class BigFatInteger
{
	int p,q;
public:
	int minOperations(int a,int b)
	{
		int i,j;
		for(i=2;i<=a;i++)
		  if(a%i==0)
		    {
			 p++;
			 j=0;
			 while(a%i==0)
			   a/=i,j++;
			 q=max(q,j);
			}
		q*=b;
		for(i=1,j=0;i<q;i*=2,j++);
		return p+j;
	}
};
