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
class History
{
	int n,m[30],x[30][30],f[30][30];
	string p,d;
public:
	string verifyClaims(vector<string> a,vector<string> b,vector<string> c)
	{
		int i,j,k;
		n=a.size();
		for(i=0;i<n;i++)
		  for(j=0;j<a[i].size();j=k+1)
		    {
			 for(k=j;k<a[i].size() && a[i][k]!=' ';k++)
			   x[i][m[i]]=x[i][m[i]]*10+a[i][k]-'0';
			 m[i]++;
			}
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(i!=j)
		      f[i][j]=1000000000;
		for(i=0;i<b.size();i++)
		  d+=b[i];
		//差分约束 
		for(i=0;i<d.size();i+=6)
		  {
		   f[d[i+0]-'A'][d[i+3]-'A']=min(f[d[i+0]-'A'][d[i+3]-'A'],x[d[i+3]-'A'][d[i+4]-'0'+1]-x[d[i+0]-'A'][d[i+1]-'0']-1);
		   f[d[i+3]-'A'][d[i+0]-'A']=min(f[d[i+3]-'A'][d[i+0]-'A'],x[d[i+0]-'A'][d[i+1]-'0'+1]-x[d[i+3]-'A'][d[i+4]-'0']-1);
		  }
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    for(k=0;k<n;k++)
		      f[j][k]=min(f[j][i]+f[i][k],f[j][k]);
		for(i=0;i<c.size();i++)
		  if(f[c[i][0]-'A'][c[i][3]-'A']>=-(x[c[i][0]-'A'][c[i][1]-'0'+1]-x[c[i][3]-'A'][c[i][4]-'0']-1)
		  && -f[c[i][3]-'A'][c[i][0]-'A']<=x[c[i][3]-'A'][c[i][4]-'0'+1]-x[c[i][0]-'A'][c[i][1]-'0']-1)
		    p.push_back('Y');
		  else
		    p.push_back('N');
		return p;
    }
};
