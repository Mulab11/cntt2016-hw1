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
class Stamp
{
	int n,m,f[100],g[100],p;
public:
	int getMinimumCost(string x,int a,int b)
	{
		int i,j,k,l,u;
		char w;
		n=x.size();
		//将两端颜色相同的*填上颜色 
		x[n]='R';
		for(i=0;i<n;i++)
		  if(x[i]=='*')
		    {
		     for(j=i;x[j+1]=='*';j++);
		     if(i==0 || j==n-1 || x[i-1]==x[j+1])
		       {
				if(i)
				  w=x[i-1];
				else
				  w=x[j+1];
				for(;i<=j;i++)
				  x[i]=w;
				i--;
			   }
			}
		//求出每段长度 
		m=1;
		for(i=0;i<n;i++)
		  {
		   if(i>0 && x[i]!=x[i-1] && x[i]!='*')
		     m++;
		   if(x[i]!='*')
		     f[m]++;
		   else
		     g[m]++;
		  }
		p=1000000000;
		for(i=1;i<=n;i++)    //枚举邮票长度 
		  {
		   //判断是否可行 
		   for(j=1,k=0;j<=m;j++)
		     if(k+f[j]+g[j]<i)
		       break;
		     else
		       k=min(g[j],k+f[j]+g[j]-i);
		   if(j<=m)
		     break;
		   //贪心求答案 
		   for(j=1,k=0,u=a*i;j<=m;j++)
		     {
			  l=(k+f[j]-1)/i+1;
			  u+=b*l;
			  k=max(0,k+f[j]+g[j]-i*l);
			 }
		   p=min(p,u);
		  }
		return p;
    }
};
