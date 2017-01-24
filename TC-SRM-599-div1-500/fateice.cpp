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
#define eps 1e-6
using namespace std;
class FindPolygons
{
	int n,x[100000],y[100000],z[100000];
	double p=1e18;
	inline void count(double a,double b,double c)
	{
		if(a<b)
		  swap(a,b);
		if(a<c)
		  swap(a,c);
		if(b<c)
		  swap(b,c);
		p=min(p,a-c);
	}
public:
	double minimumPolygon(int m)
	{
		int i,j,k;
		double w;
		if(m&1 || m==2)
		  return -1;
		//找所有勾股三角形 
		for(i=0;i<=m;i++)
		  for(j=0;j<=m;j++)
		    {
			 k=int(sqrt(i*i+j*j)+eps);
		     if(i || j)
		       if(i*i+j*j==k*k)
		         {
			      x[++n]=i;
				  y[n]=j;
				  z[n]=k;
				 }
			}
		//枚举三角形 
		for(i=1;i<n;i++)
		  for(j=i+1;j<=n;j++)
		    if(x[i]*y[j]-x[j]*y[i]!=0)
		      {
			   w=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
			   if(fabs(w+z[i]+z[j]-m)<eps)
			     count(z[i],z[j],w);
		  	  }
		if(p>1e12)
		  return m%4==2;
		else
		  return p;
	}
};
