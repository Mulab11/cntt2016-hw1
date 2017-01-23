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
#define eps 1e-6
using namespace std;
class CandyOnDisk
{
	int n;
	double l[60],r[60],d[60][60];
	bool w[60][60],p;
	inline double dis(int x,int y,int xx,int yy)
	{
		return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
	}
public:
	string ableToAchieve(vector<int> x,vector<int> y,vector<int> z,int sx,int sy,int tx,int ty)
	{
		int i,j;
		n=x.size();
		for(i=0;i<n;i++)
		  if(dis(x[i],y[i],sx,sy)<z[i]+eps)
		    l[i]=r[i]=dis(x[i],y[i],sx,sy);
		  else
		    l[i]=1e18,r[i]=-1e18;
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    d[i][j]=dis(x[i],y[i],x[j],y[j]);
		//计算起点对于每个圆可以到达的距离区间 
		while(!p)
		  {
		   p=1;
		   for(i=0;i<n;i++)
		     for(j=0;j<n;j++)
		       if((x[i]!=x[j] || y[i]!=y[j]) && !w[i][j] && l[i]<d[i][j]+z[j]+eps && d[i][j]-z[j]<r[i]+eps)
		         {
				  w[i][j]=w[j][i]=1;
				  p=0;
				  l[i]=max(min(l[i],d[i][j]-z[j]),0);
				  r[i]=min(max(r[i],d[i][j]+z[j]),z[i]);
				  l[j]=max(min(l[j],d[i][j]-z[i]),0);
				  r[j]=min(max(r[j],d[i][j]+z[i]),z[j]);
				 }
		  }
		for(i=0;i<n;i++)
		  if(l[i]<dis(x[i],y[i],tx,ty)+eps && dis(x[i],y[i],tx,ty)<r[i]+eps)
		    return "YES";
		if(sx==tx && sy==ty)
		  return "YES";
		return "NO";
    }
};
