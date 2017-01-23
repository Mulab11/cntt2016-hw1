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
class FlippingBitsDiv1
{
	int n,m,p=1000,a[1000],b[1000],c[1000][2],x[1000],y[1000],f[1000][2];
	inline void dfs(int i)
	{
		if(i*m>n)
		  {
		   int j,k;
		   for(j=n,k=0;j>0;j--)
		     {
			  k^=b[j];
			  c[j%m][k^a[j]]++;
			 }
		   for(j=0,k=0;j<m;j++)
		     {
		      k+=min(c[j][0],c[j][1]);
		      c[j][0]=c[j][1]=0;
			 }
		   for(j=1;j<=n;j++)
		     k+=b[j];
		   p=min(p,k);
		   return;
		  }
		dfs(i+1);
		b[i*m]=1;
		dfs(i+1);
		b[i*m]=0;
	}
	inline void dfs2(int i)
	{
		if(i>m)
		  {
		   int j,k;
		   for(j=1;j<=n/m;j++)
		     {
			  x[j]=y[j]=0;
		      for(k=1;k<=m;k++)
		        if(a[(j-1)*m+k]==b[k])
		          y[j]++;
		        else
		          x[j]++;
		      f[j][0]=min(f[j-1][0]+x[j],f[j-1][1]+y[j]+1);
		      f[j][1]=min(f[j-1][1]+y[j],f[j-1][0]+x[j]+1);
			 }
		   for(j=n/m*m+1,k=0;j<=n;j++)
		     if(a[j]!=b[j%m])
		       k++;
		   p=min(p,min(f[n/m][0],f[n/m][1]+1)+k);
		   return;
		  }
		dfs2(i+1);
		b[i]=1;
		dfs2(i+1);
		b[i]=0;
	}
public:
	int getmin(vector<string> t,int mm)
	{
		int i;
		string s="";
		for(i=0;i<t.size();i++)
		  s+=t[i];
		m=mm;
		n=s.size();
		for(i=1;i<=n;i++)
		  a[i]=s[i-1]-'0';
		//m小搜索前m位，m大搜索操作二 
		if(m<=17)
		  dfs2(1);
		else
		  dfs(1);
		return p;
    }
};
