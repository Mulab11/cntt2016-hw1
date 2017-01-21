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
#define inf 1000000000
using namespace std;
class MayTheBestPetWin
{
	int n,f[1000010],sa,sb,p;
public:
	int calc(vector<int> a,vector<int> b)
	{
		int i,j;
		n=a.size();
		for(i=0;i<n;i++)
		  {
		   sa+=a[i];
		   sb+=b[i];
		  }
		//dp求出每个a+b的和是否可行 
		f[0]=1;
		for(i=0;i<n;i++)
		  for(j=sa+sb;j>=a[i]+b[i];j--)
		    f[j]|=f[j-a[i]-b[i]];
		p=inf;
		for(i=0;i<=sa+sb;i++)
		  if(f[i])
		    p=min(p,max(i-sa,sb-i));
		return p;
    }
};
