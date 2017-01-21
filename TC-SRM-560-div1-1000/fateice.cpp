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
class BoundedOptimization
{
	int n,m,l[20],r[20],w[20];
	bool x[20][20];
	double f[20],p;
	inline void dfs(int i)
	{
		if(i>n)
		  {
		   int j,t=0;
		   double k;
		   for(i=1;i<=n;i++)
		     if(w[i]==1)
		       f[i]=l[i];
		     else if(w[i]==2)
		       f[i]=r[i];
		     else
		       {
				f[i]=0;
		        t++;
			   }
		   //最优情况下非边界值的变量一定两两系数不为0
		   for(i=1;i<n;i++)
		     for(j=i+1;j<=n;j++)
		       if(w[i]==3 && w[j]==3 && !x[i][j])
		         return;
		   //求出每个变量前的系数 
		   for(i=1;i<=n;i++)
		     for(j=1;j<=n;j++)
		       if(w[i]==3 && w[j]!=3 && x[i][j])
		         f[i]+=f[j];
		   //求出最优解 
		   for(i=1,k=m;i<=n;i++)
		     k-=f[i];
		   if(t)
		     k/=t;
		   else if(k<-1e-9)
		     return;
		   for(i=1;i<=n;i++)
		     if(w[i]==3)
		       f[i]+=k;
		   for(i=1;i<=n;i++)
		     if(f[i]<l[i]-1e-9 || f[i]>r[i]+1e-9)
		       break;
		   if(i<=n)
			 return;
		   for(i=1,k=0;i<n;i++)
		     for(j=i+1;j<=n;j++)
		       if(x[i][j])
		         k+=f[i]*f[j];
		   if(k>p)
		     p=k;
		   return;
		  }
		//搜索第i个变量是否为边界值 
		w[i]=1;
		dfs(i+1);
		w[i]=2;
		dfs(i+1);
		w[i]=3;
		dfs(i+1);
	}
public:
	double maxValue(vector<string> a, vector<int> ll,vector<int> rr,int mm)
	{
		int i;
		string b;
		b.clear();
		for(i=0;i<a.size();i++)
		  b+=a[i];
		for(i=0;i<b.size();i+=3)
		  x[b[i]-'a'+1][b[i+1]-'a'+1]=x[b[i+1]-'a'+1][b[i]-'a'+1]=1;
		n=ll.size();
		m=mm;
		for(i=1;i<=n;i++)
		  {
		   l[i]=ll[i-1];
		   r[i]=rr[i-1];
		  }
		dfs(1);
		return p;
    }
};
