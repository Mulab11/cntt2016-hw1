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
class FoxAndAvatar
{
    int p;
    inline void dfs(int n,int m,int w,int k)
    {
        if(w==1 && (m==1 || m==n) || n%w==1 && m==n || m==w && n<2*w || n<=w && (m==1 || m==n))  //一步结束 
          p=min(p,k);
        else if(k<=2)  //搜索只要搜两步 
          {
           int i,j;
           //下 
           dfs(((m-1)/w+1)*w,m,w,k+1);
           //上 
           for(i=1;i<=(m-1)/w;i++)
             for(j=1;j<=w;j++)
               dfs(n-i*j,m-i*j,w,k+1);
           //左 
           for(i=1;i<=(m-1)/w+1;i++)
             for(j=1;j<=(m-1)%w;j++)
               dfs(n-j*((n-1)/w-(m-1)/w-1+i)-min(j,(n-1)%w+1),m-i*j,w,k+1);
           //右 
           for(i=0;i<=(m-1)/w;i++)
             for(j=1;j<=w-(m-1)%w-1;j++)
               dfs(n-j*((n-1)/w-(m-1)/w+i)-min(max(0,(n-1)%w-(m-1)%w),j),m-i*j,w,k+1);
          }
    }
public:
	int minimalSteps(int n,int w,int m)
	{
        if(n==1)
          return 0;
        //显然存在一种4步的方案 
        p=4;
		dfs(n,m,w,1);
		return p;
    }
};
