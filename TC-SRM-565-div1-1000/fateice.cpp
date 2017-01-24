#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define inf 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define PI pair<int,int>
#define fi first
#define sc second
#define mp make_pair
using namespace std;
class UnknownTree
{
	int n,m,ans,q=1000000009;
	PI x[60];
	inline int hash(int a,int b,int c)
	{
		return (((L)a*998244353+b)%q*998244353+c)%q;
	}
	inline void count()
	{
		int i,j,k,p=1;
		sort(x+1,x+m+1);
		for(i=1;i<=m;i=j)
		  {
		   if(x[i].sc)
		     return;
		   for(j=i+1,k=0;j<=m && x[j].fi==x[i].fi;j++)
		     {
			  if(!x[j].sc)
			    return;
			  if(x[j].sc==x[j-1].sc)
			    k++;
			  else
			    k=0;
			  p=(L)p*(j-i-k)%q;
			 }
		  }
		ans=(ans+p)%q;
	}
	inline void count1(vector<int> a,vector<int> b,vector<int> c)
	{
		int i,j,k,ab,bc;
		m=0;
		for(i=0;i<n;i++)
		  {
		   if(a[i]<b[i] && b[i]<c[i])
		     j=b[i]-a[i],k=c[i]-b[i],x[++m]=mp(1,a[i]);
		   else if(a[i]>b[i] && b[i]<c[i])
		     j=a[i]-b[i],k=c[i]-b[i],x[++m]=mp(2,b[i]);
		   else if(a[i]>b[i] && b[i]>c[i])
		     j=a[i]-b[i],k=b[i]-c[i],x[++m]=mp(3,c[i]);
		   else
		     return;
		   if(i==0)
		     ab=j,bc=k;
		   else if(ab!=j || bc!=k)
		     return;
		  }
		x[++m]=mp(1,0);
		x[++m]=mp(2,0);
		x[++m]=mp(3,0);
		count();
	}
	inline void count2(vector<int> a,vector<int> b,vector<int> c,int p)
	{
		int i,j,ac=inf,ab;
		m=0;
		for(i=0;i<n;i++)
		  ac=min(ac,a[i]+c[i]);
		for(i=0;i<n;i++)
		  {
		   if(a[i]+c[i]+ac&1)
		     return;
		   j=(a[i]+c[i]-ac)/2;
		   if(a[i]<j || b[i]<j || c[i]<j)
		     return;
		   x[++m]=mp(a[i]-j,j);
		   if(i==0)
		     {
		      if(!p)
		        ab=a[i]-b[i];
		      else
		        ab=a[i]-j+b[i]-j;
		      if(ab<0 || ab>ac || b[i]==j && p)
		        return;
			 }
		   else
		     if(ab!=a[i]-b[i] && ab!=a[i]-j+b[i]-j)
		       return;
		  }
		x[++m]=mp(0,0);
		x[++m]=mp(ab,0);
		x[++m]=mp(ac,0);
		count();
	}
	inline void count3(vector<int> a,vector<int> b,vector<int> c,int w)
	{
		int i,j;
		m=0;
		for(i=0;i<n;i++)
		  {
		   if(a[i]+b[i]+a[w]+b[w]&1 || a[i]+c[i]+a[w]+c[w]&1 || b[i]+c[i]+b[w]+c[w]&1)
		     return;
		   j=min(a[i]+b[i]-a[w]-b[w],min(a[i]+c[i]-a[w]-c[w],b[i]+c[i]-b[w]-c[w]))/2;
		   if(j<0 || a[i]<j || b[i]<j || c[i]<j)
		     return;
		   if(!(a[i]-j<=a[w] && b[i]-j==a[w]+b[w]-(a[i]-j) && c[i]-j==a[w]+c[w]-(a[i]-j) || 
		        b[i]-j<=b[w] && a[i]-j==a[w]+b[w]-(b[i]-j) && c[i]-j==b[w]+c[w]-(b[i]-j) || 
		        c[i]-j<=c[w] && a[i]-j==a[w]+c[w]-(c[i]-j) && b[i]-j==b[w]+c[w]-(c[i]-j)))
		        return;
		   x[++m]=mp(hash(a[i]-j,b[i]-j,c[i]-j),j);
		  }
		x[++m]=mp(hash(0,a[w]+b[w],a[w]+c[w]),0);
		x[++m]=mp(hash(a[w]+b[w],0,b[w]+c[w]),0);
		x[++m]=mp(hash(a[w]+c[w],b[w]+c[w],0),0);
		count();
	}
public:
	int getCount(vector<int> a,vector<int> b,vector<int> c)
	{
		int i,j;
		n=a.size();
		//A-B-C且中间无点 
		count1(a,b,c);
		count1(a,c,b);
		count1(b,a,c);
		//A-B-C且中间有点 
		count2(a,b,c,0);
		count2(a,c,b,0);
		count2(b,a,c,0);
		count2(a,b,c,1);
		count2(a,c,b,1);
		count2(b,a,c,1);
		//A-x-B
		//  |
		//  C
		for(i=0;i<n;i++)
		  count3(a,b,c,i);
		return ans;
    }
};
