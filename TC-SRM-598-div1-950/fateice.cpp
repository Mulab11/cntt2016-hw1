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
#define eps 1e-9
using namespace std;
class TPS
{
	int n,f[60],p=10000;
	vector<string> s;
	inline void dfs(int i,int j)
	{
		int k,l=0;
		f[i]=0;
		for(k=0;k<n;k++)
		  if(k!=i && k!=j && s[i][k]=='Y')
		    {
			 dfs(k,i);
			 f[i]+=f[k];
			 if(!f[k])
			   if(!l)
			     l=1;
			   else
			     f[i]++;
			}
		if(j==-1)
		  p=min(p,f[i]+1);
	}
public:
	int minimalBeacons(vector<string> ss)
	{
		int i;
		s=ss;
		n=s.size();
		if(n==1)
		  return 0;
		for(i=0;i<n;i++)  //枚举其中一个信标 
		  dfs(i,-1);
		return p;
	}
};
