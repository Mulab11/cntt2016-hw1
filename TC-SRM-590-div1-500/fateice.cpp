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
class XorCards
{
	int n;
	long long p,f[60];
public:
	long long numberOfWays(vector<long long> x,long long m)
	{
		int i,j,k,w;
		long long l;
		n=x.size();
		w=50;
		for(i=w;i>=-1;i--)  //枚举哪一位小于m 
		  if(i==-1 || m&(1ll<<i))
		    {
			 //高斯消元 
			 for(j=w;j>=i && j>=0;j--)
			   {
				f[j]=0;
				for(k=0;k<n;k++)
				  if(x[k]&(1ll<<j))
				    f[j]|=(1ll<<k+1);
				if(j>i && (m&(1ll<<j)))
				  f[j]|=1;
			   }
			 for(j=w;j>=i && j>=0;j--)
			   {
				for(k=j-1;k>=i && k>=0;k--)
				  if(f[k]>f[j])
				    swap(f[j],f[k]);
				for(k=j-1;k>=i && k>=0;k--)
				  if((f[k]^f[j])<f[k])
				    f[k]^=f[j];
			   }
			 for(j=w,l=(1ll<<n);j>=i && j>=0;j--)
			   if(f[j]==1)
			     l=0;
			   else if(f[j])
			     l>>=1;
			 p+=l;
			}
		return p;
    }
};
