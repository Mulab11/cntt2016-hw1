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
class LittleElephantAndRGB
{
	int n,f[2510][2510];
	long long p;
	string s;
public:
	long long getNumber(vector<string> t,int m)
	{
		int i,j,k,l;
		for(i=0;i<t.size();i++)
		  s+=t[i];
		n=s.size();
		//dp记录末尾有几个0 
		for(i=1;i<=n;i++)
		  if(s[i-1]=='G')
		    for(j=0;j<=m;j++)
		      f[i][j]=f[i-1][max(j-1,0)]+(j<=1);
		  else
		    for(j=0;j<=m;j++)
		      f[i][j]=f[i-1][j==0?0:m]+(j==0);
		for(i=1;i<=n;i++)
		  for(j=0;j<=m;j++)
		    f[i][j]+=f[i-1][j];
		for(i=1;i<=n;i++)
		  for(j=i,k=0,l=0;j<=n;j++)
		    {
			 if(s[j-1]=='G' && k==j-i)
			   k++;
			 if(s[j-1]=='G')
			   l++;
			 else
			   l=0;
			 if(l==m)
			   k=m;
			 p+=f[i-1][max(m-k,0)];
			}
		return p;
    }
};
