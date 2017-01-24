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
struct orz
{
	int x,y;
}p[30];
class EnclosingTriangle
{
	int n,m,t,f[500010],g[500010];
	long long s[500010],q;
	void next(int &x,int &y)//求下一个点 
	{
		if(y==0 && x<m)
		  x++;
		else if(x==m && y<m)
		  y++;
		else if(y==m && x>0)
		  x--;
		else if(x==0 && y>0)
		  y--;
	}
	long long cha(int x1,int y1,int x2,int y2)   //叉乘
	{
		return (L)x1*y2-(L)x2*y1;
	}
	bool pd(int x1,int y1,int x2,int y2)   //判断所有点是否都在向量左侧 
	{
		int i;
		x2-=x1;
		y2-=y1;
		for(i=1;i<=t;i++)
		  if(cha(x2,y2,p[i].x-x1,p[i].y-y1)<0)
		    return 0;
		return 1;
	}
public:
	long long getNumber(int mm,vector<int> x,vector<int> y)
	{
		int i,j,k,l,bx,by,cx,cy,t1,t2,xx,yy;	
		m=mm;
		n=4*m;
		t=x.size();
		for(i=1;i<=t;i++)
		  {
		   p[i].x=x[i-1];
		   p[i].y=y[i-1];
		  }
		t1=m+1;bx=m;by=0;
		while(t1<n)
		  {
		   xx=bx;
		   yy=by;
		   next(xx,yy);
		   if(pd(0,0,xx,yy))
		     {
		      bx=xx;
			  by=yy;
			  t1++;
			 }
		   else
		     break;
		  }
		t2=t1;
		cx=bx;
		cy=by;
		while(t2<=n)
		  {
		   if(pd(cx,cy,0,0))
		     break;
		   t2++;
		   next(cx,cy);
		  }
		f[1]=t1;
		g[1]=t2;
		s[1]=t1;
		//利用单调性求答案 
		for(i=2,j=0,k=0;i<n;i++)
		  {
		   next(j,k);
		   while(t1<n)
		     {
			  xx=bx;
			  yy=by;
			  next(xx,yy);
		  	  if(pd(j,k,xx,yy))
		  	    {
				 bx=xx;
				 by=yy;
				 t1++;
				}
			  else
			    break;
			 }
		   f[i]=t1;s[i]=s[i-1]+f[i];
		   while(t2<=n)
		     {
			  if(pd(cx,cy,j,k))
			    break;
			  t2++;
			  next(cx,cy);
			 }
		   g[i]=t2;
		  }
		for(i=1,j=1;i<n;i++)
		  {
		   if(g[i]>n)
		     break;
		   while(j<=n && f[j]<=g[i]-1)
		     j++;
		   if(j>n)
		     break;
		   k=i+1,l=f[i]-1;
		   if(k<=l&&j<=l)
		     {
		   	  k=max(j,k);
			  q+=s[l]-s[k-1]+l-k+1-(L)g[i]*(l-k+1);
			 }
		   q+=max(f[f[i]]-max(g[i],f[i]+1)+1,0);
		  }
		return q;
	}
};
