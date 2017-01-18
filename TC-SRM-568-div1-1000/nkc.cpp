#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
#define YES return "POSSIBLE"
#define NO return "IMPOSSIBLE"
using namespace std;
struct ppp
{
	int l,r;
	void update(int x)
	{
		if(!l) l=x;
		else r=x;
	}
}b[N];
int a[N],n;
int fan[N];
struct DisjointSemicircles
{
	int to[N*N],nxt[N*N],w[N*N],pre[N],cnt,cn;
	int col[N];
	bool d[N];
	void ae(int ff,int tt,int ww)//ww=0代表相同，=1代表不同 
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		w[cnt]=ww;
		pre[ff]=cnt;
	}
	bool DFS(int x,int c)//尝试给二分图染色 
	{
		int i,j;
		col[x]=c;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(w[i]==1)
			{
				if(col[j])
				{
					if(col[j]!=3-col[x]) return false;
					else continue;
				}
				else if(!DFS(j,3-c)) return false;
			}
			else
			{
				if(col[j])
				{
					if(col[j]!=col[x]) return false;
					else continue;
				}
				else if(!DFS(j,c)) return false;
			}
		}
		return true;
	}
	bool pjiao(ppp x,ppp y)//判断两个半圆是否相交 
	{
		if(x.r>y.r) swap(x,y);
		if(y.l>x.r||y.l<x.l) return false;
		return true;
	}
	bool judge()//在已知匹配的情况下，判断能否给半圆合法定向 
	{
		cnt=0;
		memset(pre,0,sizeof(pre));
		memset(col,0,sizeof(col));
		int i,j;
		for(i=1;i<=cn;i++)
		for(j=i+1;j<=cn;j++)
		if(pjiao(b[i],b[j]))
		ae(i,j,1),ae(j,i,1);
		for(i=1;i<=cn;i++)
		if(!col[i])
		if(!DFS(i,1))
		return false;
		return true;
	}
	bool dfs(int x)//dfs配对方案 
	{
		while(x<=n&&a[x]!=-1) x++;
		if(x==n+1) return judge();
		int i;
		for(i=x+1;i<=n;i++)
		if(a[i]==-1)
		{
			cn++;
			a[x]=a[i]=cn;
			b[cn]=(ppp)
			{x,i};
			if(dfs(x+1)) return true;
			cn--;
			a[x]=a[i]=-1;
		}
		return false;
	}
	/*
	上方两个函数用于第一个暴力 
	
	下面两个函数用于第二个暴力 
	*/
	bool CHECK()//用异或前缀和判断已知部分半圆方向，其他随便配对定向，情况是否合法 
	{
		int i,j;
		for(i=1;i<=cn;i++)
		for(j=i+1;j<=cn;j++)
		if(d[i]==d[j]&&pjiao(b[i],b[j]))
		return false;
		cnt=0;
		memset(pre,0,sizeof(pre));
		memset(col,0,sizeof(col));
		for(i=1;i<=cn;i++)
		{
			if((b[i].r-b[i].l)&1)
			{
				ae(b[i].l,b[i].r-1,0);
				ae(b[i].r-1,b[i].l,0);
			}
			else
			{
				if(d[i]==1)
				{
					ae(b[i].l,b[i].r-1,0);
					ae(b[i].r-1,b[i].l,0);
				}
				else
				{
					ae(b[i].l,b[i].r-1,1);
					ae(b[i].r-1,b[i].l,1);
				}
			}
			if(d[i]==1)
			{
				ae(b[i].l-1,b[i].l,1);
				ae(b[i].l,b[i].l-1,1);
				ae(b[i].r-1,b[i].r,1);
				ae(b[i].r,b[i].r-1,1);
			}
			else
			{
				ae(b[i].l-1,b[i].l,0);
				ae(b[i].l,b[i].l-1,0);
				ae(b[i].r-1,b[i].r,0);
				ae(b[i].r,b[i].r-1,0);
			}
		}
		ae(0,n,0);
		ae(n,0,0);
		for(i=0;i<=n;i++)
		if(!col[i])
		if(!DFS(i,1))
		return false;
		return true;
	}
	bool dingxiang(int x)//给所有已知半圆定向 
	{
		if(x==cn+1) return CHECK();
		d[x]=1;
		if(dingxiang(x+1)) return true;
		d[x]=0;
		return dingxiang(x+1);
	} 
	string getPossibility(vector <int> labels)
	{
		n=labels.size();
		int i,j;
		int Free=0;
		for(i=0;i<n;i++)
		{
			if(labels[i]==-1) Free++;
			else
			{
				if(!fan[labels[i]])
				{
					cn++;
					fan[labels[i]]=cn;
				}
				b[fan[labels[i]]].update(i+1);//离散化 
			}
			a[i+1]=labels[i];
		}
		if(Free<=10)//未确定的点很少，直接枚举配对方案 
		{
			if(dfs(1)) YES;
			else NO;
		}
		else //确定的点很少，枚举这些半圆的方向 
		{
			if(dingxiang(1)) YES;
			else NO;
		}
	}
};