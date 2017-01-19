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
class LeftRightDigitsGame2
{
    int n;
    string f[60][60],g[60][60],h[60],p;   //f[i][j]表示用0~i的卡片，>=b串第j~j+i位的最小值，g表示>的最小值，h表示无要求的最小值 
    inline string minn(string a,string b)
    {
        if(a.size()<b.size())
          return a;
        if(a.size()>b.size())
          return b;
        int i,k=a.size();
        for(i=0;i<k;i++)
          {
           if(a[i]<b[i])
             return a;
           if(a[i]>b[i])
             return b;
          }
        return a;
    }
public:
	string minNumber(string a,string b)
	{
		int i,j;
		n=a.size();
		p="1000000000000000000000000000000000000000000000000000000000000";
		for(i=0;i<n;i++)
	      if(a[0]<b[i])
		    f[0][i]=g[0][i]=p;
		  else if(a[0]==b[i])
		    f[0][i]=a[0],g[0][i]=p;
		  else
		    f[0][i]=g[0][i]=a[0];
		h[0]=a[0];
		for(i=1;i<n;i++)
		  h[i]=minn(a[i]+h[i-1],h[i-1]+a[i]);
		for(i=1;i<n;i++)
		  for(j=0;j+i<n;j++)
		    {
		     f[i][j]=p;
		     if(a[i]>b[j])
		       f[i][j]=minn(f[i][j],a[i]+h[i-1]);
		     else if(a[i]==b[j])
		       f[i][j]=minn(f[i][j],a[i]+f[i-1][j+1]);
		     if(a[i]>=b[j+i])
		       f[i][j]=minn(f[i][j],f[i-1][j]+a[i]);
		     f[i][j]=minn(f[i][j],g[i-1][j]+a[i]);
		     g[i][j]=p;
		     if(a[i]>b[j])
		       g[i][j]=minn(g[i][j],a[i]+h[i-1]);
		     else if(a[i]==b[j])
		       g[i][j]=minn(g[i][j],a[i]+g[i-1][j+1]);
		     if(a[i]>b[j+i])
		       g[i][j]=minn(g[i][j],f[i-1][j]+a[i]);
		     g[i][j]=minn(g[i][j],g[i-1][j]+a[i]);
            }
        if(f[n-1][0].size()>55)
          {
           p.clear();
           return p;
          }
        else
          return f[n-1][0];
    }
};
