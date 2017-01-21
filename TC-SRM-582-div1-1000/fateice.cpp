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
class SemiPerfectPower
{
	int a[500010],u[500010],p2[500010],p3[500010],f[500010];
	vector<int> w[20000];
	inline int gcd(int a,int b)
	{
		return !b?a:gcd(b,a%b);
	}
	inline int sq2(long long n)
	{
		int i=int(sqrt(n));
		for(;(L)i*i<=n;i++);
		for(;(L)i*i>n;i--);
		return i;
	}
	inline int sq3(long long n)
	{
		int i;
		double x=sqrt(n);
		for(i=1;i<=20;i++)
		  x=(x*2+n/(x*x))/3;
		for(i=int(x);(L)i*i*i<=n;i++);
		for(;(L)i*i*i>n;i--);
		return i;
	}
	inline long long js(long long n)
	{
		int i,j,k,b,l,r,v,q;
		long long p=0;
		//统计n=ax^2 
		for(i=1;(L)i*i*i<n;i++)
		  if(p2[i])
		    p+=sq2(n/i)-i;
		//统计n=by^3 
		for(i=1;(L)i*i*i*i<n;i++)
		  if(p3[i])
		    for(j=1;j*j*j<=i;j++)
		      {
			   k=gcd(i,j*j);
			   b=i/k;
			   k=j*j/k;
			   if(p2[b])
			     {
				  q=1;
				  f[1]=1;
				  for(l=b;l>1;l/=a[l])
				    {
					 for(v=1;v<=q;v++)
					   f[v+q]=f[v]*a[l];
					 q*=2;
					}
				  for(v=1;v<=q;v++)
				    if(u[f[v]])
				      {
					   l=i/k/f[v];
					   r=sq3(n/i)/k/f[v];
					   p+=u[f[v]]*(w[f[v]][r-1]-w[f[v]][l-1]);
					  }
				 }
			  }
		return p;
	}
public:
	long long count(long long l,long long r)
	{
		int n=450000;
		int i,j,k;
		//预处理最小质因数、莫比乌斯函数、是否不包含平方/立方因子 
		for(i=2;i<=n;i++)
		  if(!a[i])
		    for(j=i;j<=n;j+=i)
		      if(!a[j])
		        a[j]=i;
		u[1]=p2[1]=p3[1]=1;
		for(i=2;i<=n;i++)
		  {
		   if(a[i/a[i]]!=a[i])
		     u[i]=-u[i/a[i]];
		   if(a[i/a[i]]!=a[i])
		     p2[i]=p2[i/a[i]];
		   if(a[i/a[i]]!=a[i] && p3[i/a[i]] || a[i/a[i]]==a[i] && a[i/(a[i]*a[i])]!=a[i] && p3[i/(a[i]*a[i])])
		     p3[i]=1;
		  }
		for(i=1;i<=17000;i++)
		  if(p2[i])
		    for(j=1,k=0;i*j<=n;j++)
		      {
			   if(p2[j] && gcd(i,j)==1)
			     k++;
			   w[i].push_back(k);
			  }
		return js(r)-js(l-1);
    }
};
