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
class EllysBulls
{
	int n,m,f[60],p,a[60][20][200],b[20];
	string q;
	vector<string> s;
	vector<int> x;
	inline void dfs(int i,string w)
	{
		int j,k=0,l,u=0,r;
		for(j=0;j<n;j++)
		  {
		   if(f[j]>x[j] || f[j]+m-i<x[j])
		     return;
		   k+=x[j]-f[j];
		  }
		if(k>b[i])
		  return;
		if(i==m)
		  {
		   p++;
		   q=w;
		   return;
		  }
		for(k='0';k<='9';k++)
		  {
		   l=0;
		   for(j=a[n][i][k];j<n;j=a[j][i][k])
		     {
		      f[j]++;
		      l=1;
			 }
		   if(l || !u)
		     {
			  if(!l)
			    r=-p;
		      dfs(i+1,w+char(k));
		      if(!l)
		        r+=p;
			 }
		   if(!l && u)
		     p+=r;
		   if(!l && !u)
		     u=1;
		   if(p>=2)
		     return;
		   for(j=a[n][i][k];j<n;j=a[j][i][k])
		     f[j]--;
		  }
	}
public:
	string getNumber(vector<string> ss,vector<int> xx)
	{
		int i,j,k,l;
		s=ss;
		x=xx;
		n=s.size();
		m=s[0].size();
		for(i=0;i<=n;i++)
		  for(j=0;j<m;j++)
		    for(k='0';k<='9';k++)
		      {
			   for(l=(i+1)%(n+1);l<n && s[l][j]!=k;l++);
			   a[i][j][k]=l;
			  }
		for(i=0;i<m;i++)
		  {
		   b[i]=0;
		   for(j='0';j<='9';j++)
		     {
			  for(k=0,l=0;k<n;k++)
			    if(s[k][i]==j)
			      l++;
			  b[i]=max(b[i],l);
			 }
		  }
		for(i=m-2;i>=0;i--)
		  b[i]+=b[i+1];
		//搜索+剪枝 
		dfs(0,"");
		if(p>=2)
		  return "Ambiguity";
		else if(p==1)
		  return q;
		else
		  return "Liar";
    }
};
