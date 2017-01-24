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
class DefectiveAddition
{
	int n,p,q=1000000007;
	inline int power(int a,int b)
	{
		if(!b)
		  return 1;
		int c=power(a,b>>1);
		c=(L)c*c%q;
		if(b&1)
		  c=(L)c*a%q;
		return c;
	}
public:
	int count(vector<int> x,int m)
	{
		int i,j,k,l,s,s0,s1;
		n=x.size();
		for(i=30;i>=0;i--)  //枚举哪一位没取满 
		  {
		   s0=1;
		   s1=0;
		   s=0;
		   l=1;
		   for(j=0;j<n;j++)
		     if(x[j]&(1<<i))
		       {
				s^=1;
				x[j]^=1<<i;
				k=s0;
				s0=((L)s0*(1<<i)+(L)s1*(x[j]+1))%q;
				s1=((L)s1*(1<<i)+(L)k*(x[j]+1))%q;
				l=(L)l*(x[j]+1)%q;
			   }
			 else
			   {
				s0=(L)s0*(x[j]+1)%q;
				s1=(L)s1*(x[j]+1)%q;
				l=(L)l*(x[j]+1)%q;
			   }
		   if(i)
		     if(s==0)
		       s0=(s0-l+q)%q;
		     else
		       s1=(s1-l+q)%q;
		   if(m&(1<<i))
		     p=(p+(L)s1*power(1<<i,q-2))%q;
		   else
		     p=(p+(L)s0*power(1<<i,q-2))%q;
		   if((m&(1<<i))!=(s<<i))
		     break;
		  }
		return p;
    }
};
