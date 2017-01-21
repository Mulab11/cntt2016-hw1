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
class SpaceWarDiv1
{
	int n,m;
	long long l,r;
	inline bool pd(long long x,vector<int> a,vector<int> b,vector<long long> c)
	{
		int i,j;
		long long k;
		for(i=j=k=0;i<n;i++)
		  {
		   while(j<m && b[j]<=a[i])
		     k+=c[j++];
		   k=max(0,k-x);
		  }
		return k==0;
	}
public:
	long long minimalFatigue(vector<int> a,vector<int> b,vector<long long> c)
	{
		int i,j;
		n=a.size();
		m=b.size();
		//排序 
		sort(&a[0],&a[0]+n);
		for(i=0;i<m;i++)
		  for(j=i+1;j<m;j++)
		    if(b[i]>b[j])
		      {
			   swap(b[i],b[j]);
			   swap(c[i],c[j]);
			  }
		//特判-1 
		if(a[n-1]<b[m-1])
		  return -1;
		//二分+贪心 
		for(l=0,r=1000000000000000000ll;l<r;)
		  if(pd(l+r>>1,a,b,c))
		    r=(l+r>>1);
		  else
		    l=(l+r>>1)+1;
		return l;
    }
};
