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
class WolfPack
{
	int n,a[100010],b[100010],q=1000000007;
	inline int C(int n,int m)
	{
		if(m<0 || m>n)
		  return 0;
		return (L)a[n]*b[m]%q*b[n-m]%q;
	}
public:
	int calc(vector<int> x,vector<int> y,int m)
	{
		int i,j,k,u=0,v=0;
		n=x.size();
		//旋转坐标轴 
		for(i=0;i<n;i++)
		  {
		   x[i]+=y[i];
		   y[i]=x[i]-2*y[i];
		  }
		//预处理组合数 
		a[0]=a[1]=b[0]=b[1]=1;
		for(i=2;i<=m;i++)
		  {
		   a[i]=(L)a[i-1]*i%q;
		   b[i]=q-(L)q/i*b[q%i]%q;
		  }
		for(i=1;i<=m;i++)
		  b[i]=(L)b[i]*b[i-1]%q;
		//枚举最终的x 
		for(i=-300000;i<=300000;i++)
		  {
		   for(j=0,k=1;j<n;j++)
		     if(m+i-x[j]&1)
		       k=0;
		     else
		       k=(L)k*C(m,(m+i-x[j])/2)%q;
		   u=(u+k)%q;
		  }
		//枚举最终的y 
		for(i=-300000;i<=300000;i++)
		  {
		   for(j=0,k=1;j<n;j++)
		     if(m+i-y[j]&1)
		       k=0;
		     else
		       k=(L)k*C(m,(m+i-y[j])/2)%q;
		   v=(v+k)%q;
		  }
		return (L)u*v%q;
    }
};
