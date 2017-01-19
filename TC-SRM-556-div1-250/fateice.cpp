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
class XorTravelingSalesman
{
    int n,f[60][1100],a[100000],b[100000],p,q;
public:
	long long maxProfit(vector<int> w,vector<string> x)
	{
		int i,j;
		n=w.size();
		f[0][w[0]]=1;
		p=1;
		q=b[1]=w[0];
		//bfs求出所有能到达的状态 
		for(i=1;i<=p;i++)
		  for(j=0;j<n;j++)
		    if(x[a[i]][j]=='Y')
		      if(!f[j][b[i]^w[j]])
		        {
                 f[j][b[i]^w[j]]=1;
                 a[++p]=j;
                 b[p]=(b[i]^w[j]);
                 q=max(q,b[i]^w[j]);
                }
        return q;
    }
};
