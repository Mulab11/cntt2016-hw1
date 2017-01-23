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
class ConvexPolygonGame
{
	int n,m,x1,y1,x2,y2,p;
	vector<int> x,y;
	inline bool pd(int xx,int yy)
	{
		int i;
		for(i=0;i<n;i++)
		  if(xx==x[i] && yy==y[i])
		    return 0;
		if(p==0)
		  {
		   p=1;
		   x1=xx;
		   y1=yy;
		   return 0;
		  }
		else if(p==1)
		  {
		   p=2;
		   x2=xx;
		   y2=yy;
		   return 0;
		  }
		if((x1-xx)*(y2-yy)-(x2-xx)*(y1-yy)==0)
		  return 0;
		else
		  return 1;
	}
public:
	string winner(vector<int> x_,vector<int> y_)
	{
		int i,j,k;
		double l,r,u;
		x=x_;
		y=y_;
		n=x.size();
		//判断是否存在不共线三点 
		for(i=-100000;i<=100000;i++)
		  {
		   for(j=0,l=1e18,r=-1e18;j<n;j++)
		     {
			  k=(j+1)%n;
		      if((i<x[k])^(i<x[j]) || i==x[k] || i==x[j])
		        {
				 if(x[j]!=x[k])
				   {
			  	    u=y[j]+double(i-x[j])/(x[k]-x[j])*(y[k]-y[j]);
			 	    l=min(l,u);
				    r=max(r,u);
				   }
			    }
			 }
		   for(j=ceil(l-eps);j<r+eps;j++)
		     if(pd(i,j))
		       return "Masha";
		  }
		return "Petya";
    }
};
