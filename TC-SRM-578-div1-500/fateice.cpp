#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<set>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class WolfInZooDivOne
{
	int n,m,l[310],r[310],f[310][310],p=1,q=1000000007;
	string s;
	vector<int> x[310];
	multiset<int> g;
	inline void get(int x[],vector<string> a)
	{
		int i,j,k;
		m=0;
		string b="";
		for(i=0;i<a.size();i++)
		  b+=a[i];
		for(i=0;i<b.size();i=j+1)
		  {
		   for(j=i,k=0;j<b.size() && b[j]>='0' && b[j]<='9';j++)
		     k=k*10+b[j]-'0';
		   x[++m]=k+1;
		  }
	}
public:
	int count(int nn,vector<string> ll,vector<string> rr)
	{
		int i,j;
		n=nn;
		get(l,ll);
		get(r,rr);
		for(i=1;i<=m;i++)
		  {
		   x[r[i]].push_back(l[i]);
		   g.insert(l[i]);
		  }
		g.insert(n);
		for(i=1;i<=n;i++)
		  {
		   int t=*g.begin();
		   f[i][0]=1;
		   //左边 
		   for(j=1;j<t;j++)
		     f[i][j]=(f[i][j]+f[j][j-1])%q;
		   //右边 
		   for(j=t;j<i;j++)
		     f[i][j]=(f[i][j]+f[j][t-1])%q;
		   //前缀和 
		   for(j=1;j<i;j++)
		     f[i][j]=(f[i][j]+f[i][j-1])%q;
		   //删除右端点为i的线段 
		   p=(p+f[i][i-1])%q;
		   for(j=0;j<x[i].size();j++)
		     g.erase(g.find(x[i][j]));
		  }
		return p;
	}
};
