#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
class MagicalHats
{
	int f[1600000],a[20],b[20],u[20],c[20],d[20],w[20];
	bool x[1600000];
public:
	int findMaximumReward(vector<string> s,vector<int> v,int q)
	{
		int n=s.size(),m=s[0].size(),p=v.size(),t=0;
		int i,j,k;
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    if(s[i][j]=='H')
		      {
			   a[t]=i;
			   b[t]=j;
			   t++;
			  }
		u[0]=1;
		for(i=1;i<=t;i++)
		  u[i]=u[i-1]*3;
		//dp求出每种情况是否可行  i中某一位为0表示帽子已掀开无硬币，为1表示帽子已掀开有硬币，为2表示帽子未掀开 
		for(i=0;i<u[t];i++)
		  {
		   for(j=0;j<t;j++)
		     if(i/u[j]%3==2)
		       break;
		   if(j<t)
		     x[i]=(x[i-u[j]]|x[i-2*u[j]]);
		   else
		     {
			  for(j=0;j<13;j++)
			    c[j]=d[j]=0;
			  for(j=0,k=0;j<t;j++)
			    {
				 c[a[j]]^=1;
				 d[b[j]]^=1;
				 if(i/u[j]%3)
				   {
					k++;
					c[a[j]]^=1;
					d[b[j]]^=1;
				   }
				}
			  if(k!=p)
			    continue;
			  for(j=0;j<13;j++)
			    if(c[j] || d[j])
			      break;
			  if(j<13)
			    continue;
			  x[i]=1;
		     }
		  }
		if(!x[u[t]-1])
		  return -1;
		//dp求出每种情况下还能获得多少硬币 
		for(i=0;i<u[t];i++)
		  {
		   if(!x[i])
		     {
			  f[i]=100;
			  continue;
			 }
		   for(j=0,k=0;j<t;j++)
		     if(i/u[j]%3==2)
		       k++;
		   if(t-k<q)
		     for(j=0;j<t;j++)
		       if(i/u[j]%3==2)
		         f[i]=max(f[i],min(f[i-u[j]]+1,f[i-2*u[j]]));
		  }
		for(i=0;i<p;i++)
		  w[i]=v[i];
		sort(w,w+p);
		for(i=0,k=0;i<f[u[t]-1];i++)
		  k+=w[i];
		return k;
	}
};
