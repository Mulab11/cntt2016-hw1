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
#define inf 1000000000000000000ll
using namespace std;
class SparseFactorial
{
	int n=1,c[1000010];
	long long a[1000010],b[1000010],p;
	inline void count(int p,int q,int r)
	{
		int i,j,k,l;
		for(i=0;i<p;i++)
		  b[i]=inf,c[i]=0;
		for(i=0;i<q*r;i++)
		  for(j=0;j<p;j+=q)
		    if(b[(j+(L)i*i)%p]==inf)
		      {
			   for(k=(j==0?p:j),l=0;k%q==0;k/=q,l++);
			   c[(j+(L)i*i)%p]+=l;
			   if(c[(j+(L)i*i)%p]>=r)
			     b[(j+(L)i*i)%p]=(L)i*i;
			  }
		for(i=n*p-1;i>=0;i--)
		  a[i]=max(a[i%n],b[i%p]);
		n*=p;
	}
public:
	long long getCount(long long l,long long r,int m)
	{
		int i,j,k,q=m;
		for(i=2;i<=m;i++)
		  if(m%i==0)  //拆成质数的幂 
		    {
			 j=1;
			 k=0;
			 while(m%i==0)
			   {
				m/=i;
				j*=i;
				k++;
			   }
			 count(j,i,k);
			}
		m=q;
		for(i=0;i<m;i++)
		  p+=max((r-((a[i]-i+m)/m*m+i)+m)/m,0)-max((l-((a[i]-i+m)/m*m+i)+m-1)/m,0);
		return p;
    }
};
