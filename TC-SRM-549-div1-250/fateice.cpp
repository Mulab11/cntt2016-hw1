#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
class PointyWizardHats
{
	bool x[60];
	int a[60],b[60];
public:
	int getNumHats(vector<int> aa,vector<int> bb,vector<int> c,vector<int> d)
	{
		int n=aa.size(),m=c.size(),p=0;
		int i,j,k;
		for(i=0;i<n;i++)
		  {
		   a[i]=aa[i];
		   b[i]=bb[i];
		  }
		//按半径从大到小排序 
		for(i=0;i<n;i++)
		  for(j=i+1;j<n;j++)
		    if(b[j]>b[i])
		      {
			   swap(a[i],a[j]);
			   swap(b[i],b[j]);
			  }
		//贪心 
		for(i=0;i<n;i++)
		  {
		   for(j=0;j<m;j++)
		     if(!x[j] && d[j]>b[i] && a[i]*d[j]>c[j]*b[i])
		       break;
		   if(j==m)
		     continue;
		   for(k=j+1;k<m;k++)
		     if(!x[k] && d[k]>b[i] && a[i]*d[k]>c[k]*b[i] && c[k]*d[j]>c[j]*d[k])
		       j=k;
		   p++;
		   x[j]=1;
		  }
		return p;
	}
};
