#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int ans=4;
struct FoxAndAvatar
{
	void dfs(int step,int n,int w,int x)//搜索 
	{
		if(step>=ans-1) return;
		if(w==1&&(x==1||x==n)) ans=step+1;
		if(n%w==1&&(x==n)) ans=step+1;
		if(x==w&&n<2*w) ans=step+1;
		if((x==1||x==n)&&n<=w) ans=step+1;
		//四种一步完成的情况 
		if(step==2) return;//因为答案最多为4，所以不是三就不用搜了 
		int h=(x-1)/w+1,l=(x-1)%w+1;
		dfs(step+1,min(h*w,n),w,x);//下面全部移除 
		int i,j;
		for(i=1;i<=w;i++)
		for(j=1;j<h;j++)
		dfs(step+1,n-i*j,w,x-i*j);//移除上方某个矩形 
		for(i=1;i<l;i++)
		for(j=1;j<=h;j++)
		{
			if(i<=(n-1)%w+1) dfs(step+1,n-((n-1)/w+1-(h-j))*i,w,x-j*i);
			else dfs(step+1,((n-1)/w)*w-((n-1)/w-(h-j))*i,w,x-i*j);
		}//移除左面一个到底的矩形 
		for(i=l+1;i<=w;i++)
		for(j=1;j<h;j++)
		{
			if(i<=(n-1)%w+1) dfs(step+1,n-((n-1)/w+1-(h-1-j))*(i-l),w,x-j*(i-l));
			else dfs(step+1,((n-1)/w)*w+min(l,(n-1)%w+1)-((n-1)/w-(h-1-j))*(i-l),w,x-j*(i-l));
		}//移除右面一个到底的矩形 
	}
	int minimalSteps(int n, int width, int x)
	{
		if(n==1) return 0;
		dfs(0,n,width,x);
		return ans;
	}
};