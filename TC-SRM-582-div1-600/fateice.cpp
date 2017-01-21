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
class ColorfulBuilding
{
	int n,f[1300][1300],s[1300],w[1300],u[1300],p,q=1000000009;
	string x,y;
public:
	long long count(vector<string> a,vector<string> b,int m)
	{
		int i,j,k;
		for(i=0;i<a.size();i++)
		  x+=a[i];
		for(i=0;i<b.size();i++)
		  y+=b[i];
		n=x.size();
		//预处理颜色 
		for(i=0;i<n;i++)
		  {
		   for(j=0;j<i;j++)
		     if(x[i]==x[j] && y[i]==y[j])
		       break;
		   u[i]=j;
		  }
		//预处理逆元 
		w[1]=1;
		for(i=2;i<=n;i++)
		  w[i]=q-(L)q/i*w[q%i]%q;
		f[u[n-1]][1]=1;
		s[1]=1;
		p=1;
		//从大到小放入 
		for(i=n-2;i>=0;i--)
		  {
		   //全局乘上颜色数不变的方案数 
		   p=(L)p*(n-i-1)%q;
		   //颜色数变化，第一个颜色一定是i的颜色 
		   for(j=n-i;j>0;j--)
		     {
			  s[j]=(s[j]+((L)f[u[i]][j]+s[j-1]-f[u[i]][j-1]+q)*w[n-i-1])%q;
			  f[u[i]][j]=(f[u[i]][j]+((L)f[u[i]][j]+s[j-1]-f[u[i]][j-1]+q)*w[n-i-1])%q;
			 }
		  }
		return (L)s[m]*p%q;
    }
};
