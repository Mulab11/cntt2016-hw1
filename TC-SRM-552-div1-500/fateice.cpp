#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class FoxAndFlowerShopDivOne
{
	int l[50][2000],r[50][2000],u[50][2000],d[50][2000],a[50][50],b[50][50];
public:
	long long theMaxFlowers(vector<string> s,int q)
	{
		int n=s.size(),m=s[0].size(),p=-10000;
		int i,j,k,ll,v,x,y;
		if(q>n*m)
		  q=n*m;
		//记录前缀和 
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    if(s[i][j]=='L')
		      {
		       a[i+1][j+1]=1;
		       b[i+1][j+1]=1;
			  }
		    else if(s[i][j]=='P')
		      {
			   a[i+1][j+1]=1;
		       b[i+1][j+1]=-1;
			  }
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    {
			 a[i][j]+=a[i][j-1];
			 b[i][j]+=b[i][j-1];
			}
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    {
			 a[i][j]+=a[i-1][j];
			 b[i][j]+=b[i-1][j];
			}
		for(i=1;i<=n;i++)
		  for(j=0;j<=2*n*m;j++)
		    u[i][j]=d[i][j]=-10000;
		for(i=1;i<=m;i++)
		  for(j=0;j<=2*n*m;j++)
		    l[i][j]=r[i][j]=-10000;
		//枚举所有矩形 
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    for(k=i;k<=n;k++)
		      for(ll=j;ll<=m;ll++)
		        {
				 x=a[k][ll]-a[i-1][ll]-a[k][j-1]+a[i-1][j-1];
				 y=b[k][ll]-b[i-1][ll]-b[k][j-1]+b[i-1][j-1]+n*m;
				 d[i][y]=max(d[i][y],x);
				 u[k][y]=max(u[k][y],x);
				 r[j][y]=max(r[j][y],x);
				 l[ll][y]=max(l[ll][y],x);
				}
		for(i=2;i<=m;i++)
		  for(j=0;j<=2*n*m;j++)
		    l[i][j]=max(l[i][j],l[i-1][j]);
		for(i=m-1;i>0;i--)
		  for(j=0;j<=2*n*m;j++)
		    r[i][j]=max(r[i][j],r[i+1][j]);
		for(i=2;i<=n;i++)
		  for(j=0;j<=2*n*m;j++)
		    u[i][j]=max(u[i][j],u[i-1][j]);
		for(i=n-1;i>0;i--)
		  for(j=0;j<=2*n*m;j++)
		    d[i][j]=max(d[i][j],d[i+1][j]);
		//枚举两个矩形的分界线 
		for(i=1;i<m;i++)
		  for(j=-n*m;j<=n*m;j++)
		    for(k=-n*m;k<=n*m;k++)
		      if(abs(j+k)<=q)
		        p=max(p,l[i][j+n*m]+r[i+1][k+n*m]);
		for(i=1;i<n;i++)
		  for(j=-n*m;j<=n*m;j++)
		    for(k=-n*m;k<=n*m;k++)
		      if(abs(j+k)<=q)
		        p=max(p,u[i][j+n*m]+d[i+1][k+n*m]);
		return p<0?-1:p;
	}
};
