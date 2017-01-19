#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class Suminator
{
	int n,m,a[100];
	long long b[100];
	inline long long js()
	{
		int i;
		m=0;
		for(i=0;i<n;i++)
		  if(a[i]>0)
		    b[++m]=a[i];
		  else if(m>1)
		    {
			 b[m-1]+=b[m];
			 m--;
			}
		return b[m];
	}
public:
	int findMissing(vector<int> x,int ans)
	{
		int i;
		long long p;
		n=x.size();
		for(i=0;i<n;i++)
		  a[i]=x[i];
		for(i=0;i<n;i++)
		  if(x[i]==-1)
		    break;
		//判断是否是0 
		a[i]=0;
		p=js();
		if(p==ans)
		  return 0;
		//判断是否是1 
		a[i]=1;
		p=js();
		if(p==ans)
		  return 1;
		if(p>ans)
		  return -1;
		//判断剩下的唯一可能 
		a[i]=ans-p+1;
		p=js();
		if(p==ans)
		  return a[i];
		else
		  return -1;
	}
};
