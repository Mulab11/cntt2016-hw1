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
inline bool cmp(int a,int b)
{
	return a>b;
}
class ICPCBalloons
{
	int n,m,t,p,q,a[100],b[100],x[100],y[100],z[100],ans;
	inline int js(int a[],int n,int x[],int p)  //贪心 
	{
		int i,k=0;
		for(i=1;i<=n;i++)
		  k+=a[i];
		for(i=1;i<=p;i++)
		  k-=x[i];
		if(k<0)
		  return 10000;
		for(i=1,k=0;i<=p;i++)
		  k+=max(0,x[i]-a[i]);
		return k;
	}
	inline void dfs(int i)   //搜索每道题的气球大小 
	{
		if(i>t)
		  {
		   ans=min(ans,js(a,n,y,p)+js(b,m,z,q));
		   return;
		  }
		y[++p]=x[i];
		dfs(i+1);
		p--;
		z[++q]=x[i];
		dfs(i+1);
		q--;
	}
public:
	int minRepaintings(vector<int> c,string d,vector<int> e)
	{
		int i;
		for(i=0;i<c.size();i++)
		  if(d[i]=='L')
		    a[++n]=c[i];
		  else
		    b[++m]=c[i];
		t=e.size();
		for(i=0;i<t;i++)
		  x[i+1]=e[i];
		sort(a+1,a+n+1,cmp);
		sort(b+1,b+m+1,cmp);
		sort(x+1,x+t+1,cmp);
		ans=10000;
		dfs(1);
		return ans==10000?-1:ans;
    }
};
