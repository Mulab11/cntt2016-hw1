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
class TrafficCongestion
{
	int f[1000010],s[1000010],q=1000000007;
public:
	int theMinCars(int n)
	{
		int i;
		f[0]=f[1]=1;
		s[0]=1;
		s[1]=2;
		//dp+前缀和 
		for(i=2;i<=n;i++)
		  {
		   f[i]=(s[i-2]*2+1)%q;
		   s[i]=(s[i-1]+f[i])%q;
		  }
		return f[n];
    }
};
