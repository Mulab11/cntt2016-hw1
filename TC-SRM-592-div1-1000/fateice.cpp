#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<complex>
#define E complex<double>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define inf 1000000000
#define pi acos(-1.0)
#define eps 1e-3
using namespace std;
class SplittingFoxes2
{
	int n,f[30],g[30];
	E a[30],b[30],c[30],d[30],e[30];
	vector<int> t;
	inline void FFT(E a[],E b[],int p)
	{
		int i,j;
		E v(1,0),u(cos(2*pi/n),p*sin(2*pi/n));
		for(i=0;i<n;i++,v*=u)
		  {
		   E w(1,0);
		   b[i]=0;
		   for(j=0;j<n;j++,w*=v)
		     b[i]+=a[j]*w;
		  }
		if(p==-1)
		  for(i=0;i<n;i++)
		    b[i]/=n;
	}
	inline bool pd()
	{
		int i;
		for(i=0;i<n;i++)
		  if(f[i]<g[i])
		    return 0;
		  else if(g[i]<f[i])
		    return 1;
	}
	inline void dfs(int i)
	{
		if(n-i<i)
		  {
		   int j;
		   for(j=0;j<n;j++)
		     d[j]=c[j];
		   FFT(d,e,-1);
		   for(j=0;j<n;j++)
		     if(fabs(e[j].imag())>eps)
		       return;
		   for(j=0;j<n;j++)
		     if(fabs(e[j].real()-int(e[j].real()+0.5))>eps)
		       return;
		   for(j=1;j<n;j++)
		     if(fabs(e[j].real()-e[n-j].real())>eps)
		       return;
		   for(j=0;j<n;j++)
		     g[j]=int(e[j].real()+0.5);
		   if(pd())
		     for(j=0;j<n;j++)
		       f[j]=g[j];
		   return;
		  }
		//点值也是对称的 
		c[i]=sqrt(b[i]);
		c[n-i]=sqrt(b[n-i]);
		dfs(i+1);
		c[i]=-c[i];
		if(n-i!=i)
		  c[n-i]=-c[n-i];
		dfs(i+1);
	}
public:
	vector<int> getPattern(vector<int> x)
	{
		int i;
		n=x.size();
		for(i=0;i<n;i++)
		  a[i]=x[i];
		//计算点值 
		FFT(a,b,1);
		f[0]=inf;
		//将点值开根 
		dfs(0);
		if(f[0]==inf)
		  t.push_back(-1);
		else
		  for(i=0;i<n;i++)
		    t.push_back(f[i]);
		return t;
    }
};
