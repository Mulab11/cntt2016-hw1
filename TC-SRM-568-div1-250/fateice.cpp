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
class BallsSeparating
{
	int n,p=1000000000;
public:
	int minOperations(vector<int> a,vector<int> b,vector<int> c)
	{
		int i,j,k,l,u;
		n=a.size();
		if(n<3)
		  return -1;
		//枚举三种颜色的球移动到哪
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    for(k=0;k<n;k++)
		      if(i!=j && j!=k && i!=k)
		        {
				 u=b[i]+c[i]+a[j]+c[j]+a[k]+b[k];
				 for(l=0;l<n;l++)
				   if(l!=i && l!=j && l!=k)
				     u+=a[l]+b[l]+c[l]-max(a[l],max(b[l],c[l]));
				 p=min(p,u);
				}
		return p;
    }
};
