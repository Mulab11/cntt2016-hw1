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
class TheBrickTowerHardDivOne
{
    int n,m,a[10000],b[10000],c[10000],x[10],y[20][20][20],u[200][200],v[200][200],p,q;
    long long w[200][200];
    inline int get(int a,int b,int c,int d)   //状压 
    {
        int i,j,k,l,p;
        i=1;
        p=1;
        if(b==a)
          j=i;
        else
          j=++p;
        if(c==a)
          k=i;
        else if(c==b)
          k=j;
        else
          k=++p;
        if(d==a)
          l=i;
        else if(d==b)
          l=j;
        else if(d==c)
          l=k;
        else
          l=++p;
        return i*1000+j*100+k*10+l;
    }
    inline void dfs(int i)
    {
        int j,k=0;
        if(i==5)
          {
           j=get(x[1],x[2],x[3],x[4]);
           a[j]=++p;
           b[j]=(x[1]==x[2])+(x[1]==x[3])+(x[2]==x[4])+(x[3]==x[4]);
           c[j]=max(max(x[1],x[2]),max(x[3],x[4]));
           return;
          }
        for(j=1;j<i;j++)
          k=max(k,x[j]);
        for(j=1;j<=k+1;j++)
          {
           x[i]=j;
           dfs(i+1);
          }
    }
    inline void dfs2(int i)
    {
        int j,k=0;
        if(i==9)
          {
           int l,w,u=1;
           j=get(x[1],x[2],x[3],x[4]);
           k=get(x[5],x[6],x[7],x[8]);
           for(l=5;l<=8;l++)
             {
              for(w=1;w<l;w++)
                if(x[l]==x[w])
                  break;
              if(w>=l)
                u=(L)u*(n-x[l]+1)%q;
             }
           l=b[k]+(x[1]==x[5])+(x[2]==x[6])+(x[3]==x[7])+(x[4]==x[8]);
           if(l<=7)
             y[a[j]][a[k]][l]=((L)y[a[j]][a[k]][l]+u)%q;
           return;
          }
        for(j=1;j<i;j++)
          k=max(k,x[j]);
        for(j=1;j<=k+1;j++)
          {
           x[i]=j;
           dfs2(i+1);
          }
    }
    inline void cheng(int v[200][200])  //矩乘 
    {
        int i,j,k,l;
        for(i=1;i<=8*p+1;i++)
          for(j=1;j<=8*p+1;j++)
            for(k=1,l=1;k<=8*p+1;k++,l++)
              {
               w[i][j]+=(L)u[i][k]*v[k][j];
               if(l==5)
                 {
                  l=0;
                  w[i][j]%=q;
                 }
              }
        for(i=1;i<=8*p+1;i++)
          for(j=1;j<=8*p+1;j++)
            {
             u[i][j]=w[i][j]%q;
             w[i][j]=0;
            }
    }
    inline int P(int i)   //求第一层的方案数 
    {
        int j,k=1;
        for(j=0;j<i;j++)
          k=(L)k*(n-j)%q;
        return k;
    }
public:
	long long find(int cc,int kk,long long h)
	{
		int i,j,k,l;
		long long r;
		n=cc;
		m=kk;
		q=1234567891;
		dfs(1);   //求出每层的状态 
		dfs2(1);  //求出相邻两层的转移 
		for(i=1;i<=p;i++)
		  for(j=1;j<=p;j++)
		    for(k=0;k<=7;k++)
		      for(l=0;k+l<=7;l++)
		        v[(j-1)*8+k+l+1][(i-1)*8+l+1]=((L)v[(j-1)*8+k+l+1][(i-1)*8+l+1]+y[i][j][k])%q;
        v[8*p+1][8*p+1]=1;
        for(i=1;i<=p;i++)
          for(j=0;j<=m;j++)
            v[8*p+1][(i-1)*8+j+1]=1;
		for(i=1;i<=8*p+1;i++)
		  u[i][i]=1;
		for(r=1;r<=h;r<<=1);
		//矩乘快速幂 
		for(r>>=1;r>0;r>>=1)
		  {
           cheng(u);
           if(h&r)
             cheng(v);
          }
        for(i=1;i<=8*p+1;i++)
          for(j=1;j<=8*p+1;j++)
            v[i][j]=0;
        for(i=1;i<=9999;i++)
          if(a[i])
            v[(a[i]-1)*8+b[i]+1][1]=P(c[i]);
        cheng(v);
		return u[8*p+1][1];
	}
};
