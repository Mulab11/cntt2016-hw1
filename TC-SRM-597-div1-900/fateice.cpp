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
#define inf 1000000000000000000ll
#define eps 1e-9
using namespace std;
class LittleElephantAndBoard
{
	int a[1000010],d[1000010],p,q=1000000007;
	int C(int n,int m)
	{
		if(m<0 || m>n)
		  return 0;
		return (L)a[n]*d[m]%q*d[n-m]%q;
	}
public:
	int getNumber(int m,int r,int g,int b)
	{
		int i;
		a[0]=d[0]=a[1]=d[1]=1;
		for(i=2;i<=m;i++)
		  {
		   a[i]=(L)a[i-1]*i%q;
		   d[i]=q-(L)q/i*d[q%i]%q;
		  }
		for(i=1;i<=m;i++)
		  d[i]=(L)d[i]*d[i-1]%q;
		r=m-r;
		g=m-g;
		b=m-b;
		if(r<g)
		  swap(r,g);
		if(r<b)
		  swap(r,b);
		if(g<b)
		  swap(g,b);
		//枚举开头/结尾有没有B，再枚举长度为偶数的段数 
		for(i=0;i<=g;i++)
		  p=(p+((L)C(r-1,i)*C(i+i,b-g-r+1+i+i)+(L)C(r,i)*C(i+i,b-g-r+i+i)*2+(L)C(r+1,i)*C(i+i,b-g-r+i+i-1))%q*C(g-1,i-1))%q;
		p=p*2%q;
		return p;
	}
};
