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
class PastingPaintingDivOne
{
	vector<long long> x;
	char s[110][110]={};
public:
	vector<long long> countColors(vector<string> a,int t)
	{
		int n=a.size(),m=a[0].size();
		int i,j,k;
		x.push_back(0);
		x.push_back(0);
		x.push_back(0);
		//t小时直接暴力 
		if(t<=50)
		  {
		   for(i=0;i<t;i++)
		     for(j=0;j<n;j++)
		       for(k=0;k<m;k++)
		         if(a[j][k]!='.')
		           s[i+j][i+k]=a[j][k];
		   for(i=0;i<t+n;i++)
		     for(j=0;j<t+m;j++)
		       if(s[i][j]=='R')
		         x[0]++;
		       else if(s[i][j]=='G')
		         x[1]++;
	   	       else if(s[i][j]=='B')
	   	         x[2]++;
	   	   return x;
		  }
		//计算前t-1个折线 
		k=1;
		for(j=0;j<n && j<m;j++)
		  {
		   for(i=0;i+j<m;i++)
		     if(!s[0][i] || s[0][i]=='.')
		       s[0][i]=a[j][i+j];
		   for(i=0;i+j<n;i++)
		     if(!s[i][0] || s[i][0]=='.')
		       s[i][0]=a[i+j][j];
		   if(j==min(n,m)-1)
		     k=t-min(n,m);
		   for(i=0;i<m;i++)
		     if(s[0][i]=='R')
		       x[0]+=k;
		     else if(s[0][i]=='G')
		       x[1]+=k;
	   	     else if(s[0][i]=='B')
	   	       x[2]+=k;
		   for(i=1;i<n;i++)
		     if(s[i][0]=='R')
		       x[0]+=k;
		     else if(s[i][0]=='G')
		       x[1]+=k;
		     else if(s[i][0]=='B')
		       x[2]+=k;
		  }
		//计算最后min(n,m)个折线 
		k=1;
		for(i=0;i<m;i++)
		  s[0][i]=0;
		for(i=0;i<n;i++)
		  s[i][0]=0;
		for(j=min(n,m)-1;j>=0;j--)
		  {
		   for(i=0;i+j<m;i++)
		     if(a[j][i+j]!='.')
		       s[0][i]=a[j][i+j];
		   for(i=0;i+j<n;i++)
		     if(a[i+j][j]!='.')
		       s[i][0]=a[i+j][j];
		   for(i=0;i<m;i++)
		     if(s[0][i]=='R')
		       x[0]+=k;
		     else if(s[0][i]=='G')
		       x[1]+=k;
	   	     else if(s[0][i]=='B')
	   	       x[2]+=k;
		   for(i=1;i<n;i++)
		     if(s[i][0]=='R')
		       x[0]+=k;
		     else if(s[i][0]=='G')
		       x[1]+=k;
		     else if(s[i][0]=='B')
		       x[2]+=k;
		  }
		return x;
    }
};
