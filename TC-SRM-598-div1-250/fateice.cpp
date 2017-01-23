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
class BinPacking
{
	int n,p,q;
	bool a[60];
public:
	int minBins(vector<int> x)
	{
		int i,j;
		n=x.size();
		sort(&x[0],&x[0]+n);
		for(i=n-1;i>=0;i--)
		  if(!a[i])
		    if(x[i]==100)
		      q++;
		    else
		      {
			   for(j=i-1;j>=0;j--)
			     if(!a[j] && x[i]+x[j]<=300)
			       break;
			   if(j>=0)
			     a[j]=1;
			   p++;
			  }
		return p+(q+2)/3;
	}
};
