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
class BitwiseAnd
{
	int m,l[60]={},r[60],x[60][60];
	bool w[60];
	vector<long long> p;
public:
	vector<long long> lexSmallest(vector<long long> a,int n)
	{
		int i,j,u;
		long long k;
		m=a.size();
		for(i=0;i<m;i++)
		  for(j=i+1;j<m;j++)
		    if(!(a[i]&a[j]))
		      return p;
		for(i=0;i<60;i++)
		  {
		   for(j=0,k=u=-1;j<m;j++)
		     if(a[j]&(1ll<<i))
		       if(k==-1)
		         k=j;
		       else if(u==-1)
		         u=j;
		       else
		         return p;
		   if(k>=0)
		     {
		      w[i]=1;
		      if(u==-1)
		        x[k][++r[k]]=i;
			 }
		  }
		for(i=m;i<n;i++)
		  {
		   k=0;
		   for(j=0;j<i;j++)
		     if(l[j]==r[j])
		       return p;
		     else
		       k|=1ll<<x[j][++l[j]];
		   for(j=0,u=n-1-i;j<60 && u>0;j++)
		     if(!w[j])
		       {
				w[j]=1;
				x[i][++r[i]]=j;
				k|=1ll<<j;
				u--;
			   }
		   if(u)
		     return p;
		   a.push_back(k);
		  }
		sort(&a[0],&a[0]+n);
		return a;
    }
};
