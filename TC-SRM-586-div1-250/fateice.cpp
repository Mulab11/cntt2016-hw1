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
class PiecewiseLinearFunction
{
	int n,p;
public:
	int maximumSolutions(vector<int> a)
	{
		int i,j,k,l;
		n=a.size();
		for(i=0;i<n-1;i++)
		  if(a[i]==a[i+1])
		    return -1;
		//枚举y 
		for(i=0;i<n;i++)
		  for(j=-1;j<=1;j++)
		    {
			 for(k=0,l=0;k<n-1;k++)
			   if(2*a[i]+j>=2*a[k] && 2*a[i]+j<2*a[k+1] || 2*a[i]+j<=2*a[k] && 2*a[i]+j>2*a[k+1])
			     l++;
			 if(2*a[i]+j==2*a[n-1])
			   l++;
			 p=max(p,l);
			}
		return p;
    }
};
