#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class TwoConvexShapes
{
	int n,m,l[100],r[100],l2[100],r2[100],f[100][100],p,q;
	inline void count()
	{
		int i,j,k;
		//黑在左，分界点单调不降 
		for(i=0;i<=n;i++)
		  for(j=0;j<=m;j++)
		    f[i][j]=0;
		f[0][0]=1;
		for(i=1;i<=n;i++)
		  for(j=0;j<=m;j++)
		    if(r[i]<=j && l2[i]>j)
		      for(k=0;k<=j;k++)
		        f[i][j]=(f[i][j]+f[i-1][k])%q;
		for(i=0;i<=m;i++)
		  p=(p+f[n][i])%q;
		//黑在左，分界点单调不增 
		for(i=0;i<=n;i++)
		  for(j=0;j<=m;j++)
		    f[i][j]=0;
		f[0][m]=1;
		for(i=1;i<=n;i++)
		  for(j=0;j<=m;j++)
		    if(r[i]<=j && l2[i]>j)
		      for(k=j;k<=m;k++)
		        f[i][j]=(f[i][j]+f[i-1][k])%q;
		for(i=0;i<=m;i++)
		  p=(p+f[n][i])%q;
		//扣去黑在左，分界为竖线 
		for(i=0;i<=m;i++)
		  {
		   for(j=1;j<=n;j++)
		     if(!(r[j]<=i && l2[j]>i))
		       break;
		   if(j>n)
		     p=(p-1)%q;
		  }
		//扣去黑在上，分界为横线，全黑在上面已经扣过 
		for(i=0;i<n;i++)
		  {
		   for(j=1;j<=i;j++)
		     if(!(l2[j]==m+1 && r2[j]==0))
		       break;
		   if(j<=i)
		     continue;
		   for(;j<=n;j++)
		     if(!(l[j]==m+1 && r[j]==0))
		       break;
		   if(j>n)
		     p=(p-1)%q;
		  }
	}
public:
	int countWays(vector<string> a)
	{
		int i,j;
		n=a.size();
		m=a[0].size();
		q=1000000007;
		//预处理每种颜色在每行的最左和最右的点  
		for(i=0;i<n;i++)
		  {
		   l[i+1]=l2[i+1]=m+1;
		   r[i+1]=r2[i+1]=0;
		   for(j=0;j<m;j++)
			 {
		      if(a[i][j]=='B')
		        r[i+1]=j+1;
		      else if(a[i][j]=='W')
		        r2[i+1]=j+1;
		      if(a[i][m-1-j]=='B')
		        l[i+1]=m-j;
		      else if(a[i][m-1-j]=='W')
		        l2[i+1]=m-j;
			 }
		  }
		//统计黑色在左/上的答案 
		count();
		//统计白色在左/上的答案 
		for(i=1;i<=n;i++)
		  {
		   swap(l[i],l2[i]);
		   swap(r[i],r2[i]);
		  }
		count();
		return (p+q)%q;
	}
};
