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
class CuttingBitString
{
    int n,f[100];
    inline bool pd(int l,int r,string a)  //判断一段是否是5的幂 
    {
        if(a[l]=='0')
          return 0;
        int i;
        long long k=0;
        for(i=l;i<=r;i++)
          k=(k<<1)+a[i]-'0';
        while(k%5==0)
          k/=5;
        return k==1;
    }
public:
	long long getmin(string a)
	{
		int i,j;
		n=a.size();
		for(i=1;i<=n;i++)  //dp 
		  {
           f[i]=10000;
		   for(j=0;j<i;j++)
		     if(pd(j,i-1,a))
		       f[i]=min(f[i],f[j]+1);
          }
        return f[n]==10000?-1:f[n];
    }
};
