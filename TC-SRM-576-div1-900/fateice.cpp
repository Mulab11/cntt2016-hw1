#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class CharacterBoard
{
	int n,m,x[5000000],p,q=1000000009,ans=0,w;
	vector<string> s;
	map<int,char> f; 
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
	inline void count(int x)
	{
		int i,j,k=0;
		if(x>=n*m)
		  ans=(ans+q-power(26,x-n*m))%q;
		f.clear();
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    if(!f[((L)i*w+j)%x])
		      f[((L)i*w+j)%x]=s[i][j],k++;
		    else if(f[((L)i*w+j)%x]!=s[i][j])
		      return;
		ans=(ans+power(26,x-k))%q;
	}
public:
	int countGenerators(vector<string> ss,int ww,int i0,int j0)
	{
		int i,j,l;
		long long k;
		s=ss;
		n=s.size();
		m=s[0].size();
		w=ww;
		for(i=0;i<n;i++)
		  for(j=-(m-1);j<m;j++)
		    {
			 k=i*w+j;
			 for(l=1;(L)l*l<=k;l++)
			   if(k%l==0)
			     {
				  if(l<=w)
			        x[++p]=l;
			      if(k/l<=w)
			        x[++p]=k/l;
				 }
			}
		for(i=1;i<n*m && i<=w;i++)
		  x[++p]=i;
		sort(x+1,x+p+1);
		//等比数列 
		ans=(L)(power(26,max(w-n*m+1,0))+q-1)*power(25,q-2)%q;
		//特殊值单独求 
		for(i=1;i<=p;i++)
		  if(x[i]!=x[i-1])
		    count(x[i]);
		return ans;
    }
};
