#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define mxx(a,b) ((a)>(b)?(a):(b))
#define pi 3.1415926535897932
using namespace std;
class FencingPenguins
{
	int m,b[300],f[300][300],g[300][300],h[300][300][2],q=100007;
	double xx[300],yy[300];
	long long s[300][300],c[300][300];
	bool z[300][300];
public:
	double cha(double x1,double y1,double x2,double y2,double x3,double y3)  //叉乘 
	{
		return (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
	}
	int countWays(int n,int r,vector<int> x,vector<int> y,string a)
	{
		int i,j,k,l,u,w;
		m=x.size();
		for(i=0;i<m;i++)
		  if(a[i]<='Z')
		    b[i]=a[i]-'A';
		  else
		    b[i]=a[i]-'a'+26;
		for(i=0;i<n;i++)
		  {
		   xx[i]=r*cos(2*pi/n*i);
		   yy[i]=r*sin(2*pi/n*i);
		  }
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    for(k=0;k<m;k++)
			  if(cha(xx[i],yy[i],xx[j],yy[j],x[k],y[k])>=0)
			    {
			     s[i][j]|=1ll<<k;
				 c[i][j]|=1ll<<b[k];
				}
		if(s[0][n-1])
		  return 0;
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    z[i][j]=!(c[i][j]&c[j][i]);
		for(i=0;i<n;i++)
		  h[i][i][1]=1;
		//dp考虑每个圆弧 
		for(u=1;u<n;u++)
		  for(int i=0;i+u<n;i++)
		    {
			 j=i+u;
			 for(k=0;k<=1;k++)
			   for(l=i+1;l<=j;l++)
			     if(z[i][l])
				   {
				    w=h[l][j][k||(s[i][l]&s[l][j]&s[j][i])];
				    if(!s[l][i])
					  h[i][j][k]=(h[i][j][k]+w)%q;
					else if(l-i>3&&!(s[l][i]&s[i+1][l-1]))
					  h[i][j][k]=(h[i][j][k]+(L)w*f[i+1][l-1])%q;
			       }
			 for(k=i+2;k<=j;k++)
			   if(z[i][k])
			     if(!(s[j][i]&s[i][k]))
				   g[i][j]=(g[i][j]+h[i][k][0])%q;
				else if(k<j-2 && !(s[j][i]&s[i][k]&s[k+1][j]))
				   g[i][j]=(g[i][j]+(L)f[k+1][j]*h[i][k][0])%q;
			 for(k=i;k<=j;k++)
			   if(!(s[j][i]&s[k][j]))
			     f[i][j]=(f[i][j]+g[k][j])%q;
		    }
		return f[0][n-1];
	}
};
