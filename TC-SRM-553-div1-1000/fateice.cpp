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
class YamanoteLine
{
    int n;
	long long f[60][60][110];
	inline void add(int i,int j,int k,int l)
	{
        f[i][j][k+n]=min(f[i][j][k+n],l);
    }
public:
	long long howMany(int m,vector<int>s1,vector<int>t1,vector<int>l1,vector<int>s2,vector<int>t2,vector<int>l2)
	{
		int i,j,k,u;
		long long l,r;
		n=m;
		//建立带未知数差分约数系统，k表示未知数前的系数 
		for(i=0;i<=n;i++)
		  for(j=0;j<=n;j++)
		    for(k=0;k<=2*n;k++)
		      f[i][j][k]=1000000000000000000ll;
		for(i=0;i<=n;i++)
		  f[i][i][n]=0;
		for(i=0;i<n;i++)
		  add(i+1,i,0,-1);
		add(0,n,1,0);
		add(n,0,-1,0);
		for(i=0;i<s1.size();i++)
		  if(s1[i]<t1[i])
		    add(t1[i],s1[i],0,-l1[i]);
		  else
		    add(t1[i],s1[i],1,-l1[i]);
		for(i=0;i<s2.size();i++)
		  if(s2[i]<t2[i])
		    add(s2[i],t2[i],0,l2[i]);
		  else
		    add(s2[i],t2[i],-1,l2[i]);
		//floyd求最短路 
		for(i=0;i<=n;i++)
		  for(j=0;j<=n;j++)
		    for(k=0;k<=n;k++)
		      for(l=-n;l<=n;l++)
		        for(u=max(-n,-n-l);u<=min(n,n-l);u++)
		          f[j][k][l+u+n]=min(f[j][k][l+u+n],f[j][i][l+n]+f[i][k][u+n]);
		l=n;
		r=1000000000000000000ll;
		//每个环必须为正 
		for(i=0;i<=n;i++)
		  for(j=-n;j<=n;j++)
		  {
		    if(j>0)
		      l=max(l,(-f[i][i][j+n]+j-1)/j);
		    else if(j<0)
		      r=min(r,f[i][i][j+n]/(-j));
		    else if(f[i][i][j+n]<0)
		      return 0;
          }
		if(l>r)
		  return 0;
		if(r>1000000000000000ll)
		  return -1;
		return r-l+1;
	}
};
