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
class TheSquareRootDilemma
{
	int n,a[80000],b[80000],p;
public:
	int countPairs(int n,int m)
	{
		int i,j,k;
		for(i=1;i<=n;i++)
		  {
		   for(j=i,k=2;k*k<=j;k++)   //去平方因子 
		     while(j%(k*k)==0)
		       j/=k*k;
		   a[j]++;
		  }
		for(i=1;i<=m;i++)
		  {
		   for(j=i,k=2;k*k<=j;k++)
		     while(j%(k*k)==0)
		       j/=k*k;
		   b[j]++;
		  }
		for(i=1;i<=n;i++)
		  p+=a[i]*b[i];
		return p;
    }
};
