#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct GearsDiv1
{
	int col[N];
	int to[N*N],nxt[N*N],pre[N],cnt;
	void ae(int ff,int tt)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
	}
	bool used[N];
	int c[N];
	bool find(int x)//匈牙利算法 
	{
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(used[j]) continue;
			used[j]=true;
			if(!c[j]||find(c[j]))
			{
				c[j]=x;
				return true;
			}
		}
		return false;
	}
	int getmin(string color, vector <string> graph)
	{
		int n=color.size();
		int i,j,k;
		for(i=0;i<n;i++)
		{
			if(color[i]=='R') col[i]=0;
			else if(color[i]=='B') col[i]=1;
			else col[i]=2;
		}
		int ans=1e9;
		for(k=0;k<=2;k++)//枚举方向不同的一种颜色 
		{
			cnt=0;
			memset(pre,0,sizeof(pre));
			for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			if(graph[i][j]=='Y')
			if(col[i]!=k&&col[j]!=k)//冲突的建边 
			{
				if(col[i]<col[j]) ae(i,j);
				else ae(j,i);
			}
			int T=0;
			if(k==0) T=1;
			int now=0;
			memset(c,0,sizeof(c));
			for(i=0;i<n;i++)
			if(col[i]==T)//跑二分图最大点独立集 
			{
				memset(used,0,sizeof(used));
				if(find(i)) now++;
			}
			ans=min(ans,now);
		}
		return ans;
	}
};