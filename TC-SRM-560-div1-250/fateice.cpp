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
class TomekPhone
{
public:
	int minKeystrokes(vector<int> x,vector<int> y)
	{
	    int n,m,p=0;
	    int i,j,k;
	    n=x.size();
	    m=y.size();
	    sort(&x[0],&x[n-1]+1);
	    sort(&y[0],&y[m-1]+1);
	    for(i=n-1,j=0,k=m-1;i>=0;i--)
	      {
		   if(k==m-1)
		     {
			  j++;
			  k=-1;
			 }
		   for(k++;k<m && y[k]<j;k++);
		   if(k==m)
		     return -1;
		   p+=x[i]*j;
		  }
		return p;
    }
};
