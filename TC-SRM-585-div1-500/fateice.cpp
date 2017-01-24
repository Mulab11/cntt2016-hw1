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
class LISNumber
{
	int n,f[1500][1500],x[1500],p=1,q=1000000007;
	inline int power(int a,int b)
	{
		if(!b)
		  return 1;
		int c=power(a,b>>1);
		c=(L)c*c%q;
		if(b&1)
		  c=(L)c*a%q;
		return c;
	}
public:
	int count(vector<int> a,int m)
	{
		int i,j;
		for(i=0;i<a.size();i++)
		  for(j=1;j<=a[i];j++)
		    {
		     x[++n]=j-1;
		     p=(L)p*power(j,q-2)%q;
			}
		//dp将数从小到大插入 
		f[0][0]=1;
		for(i=1;i<=n;i++)
		  for(j=0;j<=m;j++)
		    {
			 f[i][j]=(f[i][j]+(L)f[i-1][j]*(j-x[i]))%q;
			 f[i][j+1]=(f[i][j+1]+(L)f[i-1][j]*(i-j+x[i]))%q;
			}
		return int((L)f[n][m]*p%q);
    }
};
