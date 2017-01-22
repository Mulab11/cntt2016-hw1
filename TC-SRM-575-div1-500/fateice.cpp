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
class TheSwapsDivOne
{
	int n;
	string s;
	double p,w,f[1000010];
public:
	double find(vector<string> t,int m)
	{
		int i;
		for(i=0;i<t.size();i++)
		  s+=t[i];
		n=s.size();
		f[0]=1;
		//计算i轮后每个数在原先位置上的概率 
		for(i=1;i<=m;i++)
		  f[i]=f[i-1]*(n-2)/n+(1-f[i-1])*2/n/(n-1);
		for(i=1;i<=n;i++)
		  w+=(double)i*(n-i+1)/n/(n+1)*2;
		for(i=1;i<=n;i++)
		  p+=(s[i-1]-'0')*(f[m]*i*(n-i+1)/n/(n+1)*2+(1-f[m])*(w-(double)i*(n-i+1)/n/(n+1)*2)/(n-1));
		return p;
    }
};
