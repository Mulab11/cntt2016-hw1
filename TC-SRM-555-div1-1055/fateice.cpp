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
class MapGuessing
{
    int n,m,t;
    char a[40],b[600],c[40];
    long long x[40],p;
    inline void js(int i)  //计算起始位置在i时，有哪些位置可以随意确定 
    {
        int j,k,l=0;
        for(j=1;j<=n;j++)
          c[j]=0;
        for(j=1,k=i;j<=m;j++)
          {
           if(b[j]=='<')
             k--;
           else if(b[j]=='>')
             k++;
           else
             {
              if(c[k]!=0 && c[k]!=a[k])
                l--;
              c[k]=b[j];
              if(c[k]!=a[k])
                l++;
             }
           if(k<1 || k>n)
             {
              x[i]=-1;
              return;
             }
           if(l==0)
             {
              for(l=1;l<=n;l++)
                if(c[l]==a[l])
                  x[i]|=(1ll<<l-1);
              l=0;
             }
          }
    }
    inline int lb(long long k)   //求出k在二进制下1的个数 
    {
        int p=0;
        while(k)
          {
           p+=(k&1);
           k>>=1;
          }
        return p;
    }
    inline void dfs(int i,int j,long long k)  //容斥 
    {
        if(i>t)
          {
           p+=j*(1ll<<lb(k));
           return;
          }
        if(k==0)
          return;
        dfs(i+1,j,k);
        dfs(i+1,-j,k&x[i]);
    }
public:
	long long countPatterns(string aa,vector<string> bb)
	{
		int i,j;
		n=aa.size();
		for(i=1;i<=n;i++)
		  a[i]=aa[i-1];
		for(i=0;i<bb.size();i++)
		  {
           for(j=1;j<=bb[i].size();j++)
             b[m+j]=bb[i][j-1];
           m+=bb[i].size();
          }
        for(i=1;i<=n;i++)
          js(i);
        for(i=1,t=0;i<=n;i++)
          if(x[i]>=0)
            x[++t]=x[i];
        dfs(1,1,(1ll<<n)-1);
        return (1ll<<n)-p;
    }
};
