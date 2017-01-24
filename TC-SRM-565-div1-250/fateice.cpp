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
class MonstersValley
{
	int n;
	long long f[60][110];
public:
	int minimumPrice(vector<long long> a,vector<int> b)
	{
		int i,j;
		n=a.size();
		for(i=0;i<=n;i++)
		  for(j=0;j<=2*n;j++)
		    f[i][j]=-1000000000000000000ll;
		f[0][0]=0;
		//dp
		for(i=1;i<=n;i++)
		  for(j=0;j<=2*n;j++)
		    {
		     if(f[i-1][j]>=a[i-1])
		       f[i][j]=max(f[i][j],f[i-1][j]);
		     if(j>=b[i-1])
		       f[i][j]=max(f[i][j],f[i-1][j-b[i-1]]+a[i-1]);
			}
		for(i=0;i<=2*n;i++)
		  if(f[n][i]>=0)
		    return i;
    }
};
