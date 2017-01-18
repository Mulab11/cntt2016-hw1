#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 20010
#define M 400010
using namespace std;
int to[N],nxt[N],pre[N],cnt;
void ae(int ff,int tt)
{
	cnt++;
	to[cnt]=tt;
	nxt[cnt]=pre[ff];
	pre[ff]=cnt;
}
int SG[N],fa[N];
int rt[N];
int ch[M][2],siz[M],tg[M],cn;
void pup(int x)
{siz[x]=siz[ch[x][0]]+siz[ch[x][1]];}
void pud(int x,int k)
{
	if(!x) return;
	if(tg[x]&(1<<k))
	{
		tg[x]-=(1<<k);
		swap(ch[x][0],ch[x][1]);
		tg[ch[x][0]]^=tg[x];
		tg[ch[x][1]]^=tg[x];
		tg[x]=0;
	}
	else
	{
		tg[ch[x][0]]^=tg[x];
		tg[ch[x][1]]^=tg[x];
		tg[x]=0;
	}
}
int merge(int x,int y,int k)
{
	if(k==0)
	{
		siz[x]=max(siz[x],siz[y]);
		return x;
	}
	pud(x,k-1);pud(y,k-1);
	if(!y||!x) return x+y;
	ch[x][0]=merge(ch[x][0],ch[y][0],k-1);
	ch[x][1]=merge(ch[x][1],ch[y][1],k-1);
	pup(x);
	return x;
}
void add(int &x,int v,int k)
{
	if(!x) cn++,x=cn;
	if(k==0)
	{
		siz[x]=1;
		return;
	}
	pud(x,k-1);
	if(v&(1<<(k-1))) add(ch[x][1],v,k-1);
	else add(ch[x][0],v,k-1);
	pup(x);
}
int getmin(int x,int k)
{
	if(!x||k==0) return 1;
	pud(x,k-1);
	if(siz[ch[x][0]]!=(1<<(k-1))) return getmin(ch[x][0],k-1);
	else return (1<<(k-1))+getmin(ch[x][1],k-1);
}
void dfs(int x)//用线段树合并+字典树O(nlogn)计算 
{
	int i,j,tmp=0;
	bool ns=true;
	for(i=pre[x];i;i=nxt[i])
	{
		j=to[i];
		if(j==fa[x]) continue;
		fa[j]=x;
		ns=false;
		dfs(j);
		tmp^=SG[j];
	}
	for(i=pre[x];i;i=nxt[i])
	{
		j=to[i];
		if(j==fa[x]) continue;
		rt[x]=merge(rt[x],rt[j],16);
	}
	if(ns)
	{
		add(rt[x],1,16);
		SG[x]=1;
		return;
	}
	add(rt[x],0,16);
	tg[rt[x]]^=tmp;
	SG[x]=getmin(rt[x],16)-1;
	tg[rt[x]]^=SG[x];
}
int du[N];
struct circle
{int x,y,r;}C[N];
bool cmp(circle x,circle y)
{return x.r<y.r;}
bool sel[N];
struct CirclesGame
{
	int sqr(int x)
	{return x*x;}
	string whoCanWin(vector <int> x, vector <int> y, vector <int> r)
	{
		int n=x.size();
		int i,j;
		for(i=0;i<n;i++)
		C[i+1]=(circle)
		{x[i],y[i],r[i]};
		sort(C+1,C+n+1,cmp);
		for(i=1;i<=n;i++)
		for(j=1;j<i;j++)
		if(!sel[j]&&C[i].r>C[j].r)
		{
			if(sqr(C[i].r)>sqr(C[i].x-C[j].x)+sqr(C[i].y-C[j].y))//建图 
			{
				sel[j]=true;
				ae(i,j);
				du[j]++;
			}
		}
		int ans=0;
		for(i=1;i<=n;i++)
		if(!du[i])//组合游戏求SG值 
		{
			dfs(i);
			ans^=SG[i];
		}
		if(ans==0) return "Bob";
		else return "Alice";
	}
}; 