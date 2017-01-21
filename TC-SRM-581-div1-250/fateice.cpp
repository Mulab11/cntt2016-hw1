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
class SurveillanceSystem
{
	int n,m,s[60],f[60],g[60],x[60];
	string p;
public:
	string getContainerInfo(string a,vector<int> b,int l)
	{
		int i,j;
		n=a.size();
		m=b.size();
		for(i=0;i<m;i++)
		  x[b[i]]++;
		for(i=0;i<n;i++)
		  s[i+1]=s[i]+(a[i]=='X');
		for(i=1;i<=n;i++)
		  {
		   for(j=0;j<=n;j++)
		     f[j]=g[j]=0;
		   //统计有多少个包含i和不包含i的区间恰有x个'X' 
		   for(j=1;j+l-1<=n;j++)
		     if(j>i || j+l<=i)
		       f[s[j+l-1]-s[j-1]]++;
		     else
		       g[s[j+l-1]-s[j-1]]++;
		   for(j=0;j<=n;j++)
		     if(x[j] && g[j])
		       break;
		   if(j<=n)
		     {
			  for(j=0;j<=n;j++)
			    if(x[j]>f[j])
			      break;
			  if(j<=n)
			    p.push_back('+');
			  else
			    p.push_back('?');
			 }
		   else
		     p.push_back('-');
		  }
		return p;
    }
};
