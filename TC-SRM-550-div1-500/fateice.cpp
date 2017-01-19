#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
class CheckerExpansion
{
	inline bool pd(long long x,long long y,long long t)   //判断C((x+y)/2,y)是否为奇数 
	{
		long long i;
		if(x+y&1)
		  return 0;
		x=(x+y>>1);
		if(x>=t || y>x)
		  return 0;
		for(i=1;x>>i;i++)
		  if((x>>i)>(y>>i)+(x-y>>i))
		    return 0;
		return 1;
	}
public:
	vector<string> resultAfter(long long t,long long x0,long long y0,int w,int h)
	{
		long long x,y;
		vector<string> a;
		string b;
		a.clear();
		for(y=y0+h-1;y>=y0;y--)
		  {
		   b.clear();
		   for(x=x0;x<x0+w;x++)
		     if(pd(x,y,t))
		       if(x+y&2)
		         b.push_back('B');
		       else
		         b.push_back('A');
		     else
		       b.push_back('.');
		   a.push_back(b);
		  }
		return a;
	}
};
