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
struct line
{
	int l,r;
}a[3000];
inline bool cmp(line a,line b)
{
	return a.l<b.l;
}
class ShoutterDiv1
{
	int n,x[10010],p;
	inline void getl(vector<string> c,int x)
	{
		int i;
		string b;
		b.clear();
		for(i=0;i<c.size();i++)
		  b+=c[i];
		n=b.size();
		for(i=0;i<n;i++)
		  a[i+1].l+=(b[i]-'0')*x;
	}
	inline void getr(vector<string> c,int x)
	{
		int i;
		string b;
		b.clear();
		for(i=0;i<c.size();i++)
		  b+=c[i];
		n=b.size();
		for(i=0;i<n;i++)
		  a[i+1].r+=(b[i]-'0')*x;
	}
public:
	int count(vector<string> s1000,vector<string> s100,vector<string> s10,vector<string> s1,vector<string> t1000,vector<string> t100,vector<string> t10,vector<string> t1)
	{
		int i,j,k;
		getl(s1000,1000);
		getl(s100,100);
		getl(s10,10);
		getl(s1,1);
		getr(t1000,1000);
		getr(t100,100);
		getr(t10,10);
		getr(t1,1);
		sort(a+1,a+n+1,cmp);
		//判断答案是否为-1 
		for(i=2,j=a[1].r;i<=n;i++)
		  {
		   if(j<a[i].l)
		     return -1;
		   j=max(j,a[i].r);
		  }
		//计算右端点为i时加一个区间所能到达的最大右端点 
		for(i=1;i<=n;i++)
		  x[a[i].l]=max(x[a[i].l],a[i].r);
		for(i=1;i<10000;i++)
		  x[i]=max(x[i],x[i-1]);
		for(i=1,k=10000;i<=n;i++)
		  k=min(k,a[i].r);
		for(i=1;i<=n;i++)
		  for(j=k;j<a[n].l;j=x[j],p++)
		    if(j>=a[i].l)  //区间i可以直接选 
		      {
			   j=max(j,a[i].r);
			   if(j>=a[n].l)
			     break;
			  }
		return p;
    }
};
