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
#define inf 1000000000
using namespace std;
class TheTree
{
	int n,p;
public:
	int maximumDiameter(vector<int> x)
	{
		int i,j;
		n=x.size();
		for(i=n-1,j=n;i>=0;i--) //枚举lca深度 
		  {
		   if(x[i]==1)
		     j=i;
		   p=max(p,n+j-2*i);
		  }
		return p;
    }
};
