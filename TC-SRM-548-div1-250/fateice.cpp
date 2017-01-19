#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
class KingdomAndTrees
{
public:
	int minLevel(vector<int> a)
	{
		int n=a.size();
		int i,j,l=0,r=1000000000;
		//二分答案 
		while(l<r)
		  {
		   int m=(l+r>>1);
		   for(i=1,j=max(1,a[0]-m);i<n && j<a[i]+m;i++)
		     j=max(j+1,a[i]-m);
		   if(i<n)
		     l=(l+r>>1)+1;
		   else
		     r=(l+r>>1);
		  }
		return l;
	}
};
