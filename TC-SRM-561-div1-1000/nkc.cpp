#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 2510
#define can(x,y) (!(x<0||x>=hang||y<0||y>lie||field[x][y]=='#'))
using namespace std;
int a[51][51];
int sit[N],m;
int hang,lie;
struct Orienteering
{
	int n;
	int to[N<<1],nxt[N<<1],pre[N],cnt;
	int siz[N],fa[N],fan[N];
	int d[310][310];
	void ae(int ff,int tt)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
	}
	void build(int x)
	{
		int i,j;
		siz[x]=(fan[x]!=0);
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa[x]) continue;
			fa[j]=x;
			build(j);
			siz[x]+=siz[j];
		}
	}
	void getd(int x,int fa,int dis,int X)//处理每个点的距离 
	{
		if(fan[x])
		d[X][fan[x]]=dis;
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa) continue;
			getd(j,x,dis+1,X);
		}
	}
	bool comp(int d1,int a1,int b1,int d2,int a2,int b2)//按照三个关键字比较距离的大小 
	{
		if(d1!=d2) return d1>d2;
		if(a1!=a2) return a1<a2;
		return b1<b2;
	}
	double expectedLength(vector <string> field, int K)
	{
		int i,j,k,si,sj,x,y;
		hang=field.size();
		lie=field[0].size();
		for(i=0;i<hang;i++)
		for(j=0;j<lie;j++)
		if(field[i][j]!='#')
		{
			m++;a[i][j]=m;
			if(field[i][j]=='*') 
			{n++;sit[n]=m;fan[m]=n;}
			if(can(i,j-1)) ae(m-1,m),ae(m,m-1);
			if(can(i-1,j)) ae(a[i-1][j],m),ae(m,a[i-1][j]);
		}
		build(1);
		double ans=0,tot=0;
		for(i=2;i<=m;i++)//先计算每条边在树上的期望 
		{
			x=siz[i];ans=0;
			if(x>=K)
			{
				double tmp=1;
				for(j=0;j<K;j++)//为了防止爆炸需要一边乘一边除 
				tmp=tmp*(x-j)/(n-j);
				ans+=tmp;
			}
			x=n-siz[i];
			if(x>=K)
			{
				double tmp=1;
				for(j=0;j<K;j++)
				tmp=tmp*(x-j)/(n-j);
				ans+=tmp;
			}
			tot+=2*(1-ans);
		}
		for(i=1;i<=n;i++)
		getd(sit[i],0,0,i);//预处理两两关键点之间的距离 
		//记下来计算最长路径的期望 
		for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)//枚举最长路径的两个端点 
		{
			int tmp=0;
			for(k=1;k<=n;k++)
			if(i!=k&&j!=k)
			{
				if(comp(d[i][j],i,j,d[i][k],min(i,k),max(i,k))
				 &&comp(d[i][j],i,j,d[j][k],min(j,k),max(j,k)))
		 		tmp++;
			}//统计符合条件的其他点的个数 
			ans=d[i][j];
			if(tmp>=K-2)
			{
				for(k=0;k<K-2;k++)
				ans=ans*(tmp-k)/(n-2-k);
			}
			else ans=0;
			ans=ans*K/n*(K-1)/(n-1);
			tot-=ans;
		}
		return tot;
	}
};